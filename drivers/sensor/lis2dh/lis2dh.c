/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT st_lis2dh


#include <init.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(lis2dh, CONFIG_SENSOR_LOG_LEVEL);
#include "lis2dh.h"

#define ACCEL_SCALE(sensitivity)			\
	((SENSOR_G * (sensitivity) >> 14) / 100)

/*
 * Use values for low-power mode in DS "Mechanical (Sensor) characteristics",
 * multiplied by 100.
 */
static uint32_t lis2dh_reg_val_to_scale[] = {
	ACCEL_SCALE(1600),
	ACCEL_SCALE(3200),
	ACCEL_SCALE(6400),
	ACCEL_SCALE(19200),
};

static void lis2dh_convert(int16_t raw_val, uint32_t scale,
			   struct sensor_value *val)
{
	int32_t converted_val;

	/*
	 * maximum converted value we can get is: max(raw_val) * max(scale)
	 *	max(raw_val >> 4) = +/- 2^11
	 *	max(scale) = 114921
	 *	max(converted_val) = 235358208 which is less than 2^31
	 */
	converted_val = (raw_val >> 4) * scale;
	val->val1 = converted_val / 1000000;
	val->val2 = converted_val % 1000000;
}

static int lis2dh_channel_get(const struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct lis2dh_data *lis2dh = dev->data;
	int ofs_start;
	int ofs_end;
	int i;

	switch (chan) {
	case SENSOR_CHAN_ACCEL_X:
		ofs_start = ofs_end = 0;
		break;
	case SENSOR_CHAN_ACCEL_Y:
		ofs_start = ofs_end = 1;
		break;
	case SENSOR_CHAN_ACCEL_Z:
		ofs_start = ofs_end = 2;
		break;
	case SENSOR_CHAN_ACCEL_XYZ:
		ofs_start = 0;
		ofs_end = 2;
		break;
	default:
		return -ENOTSUP;
	}
	for (i = ofs_start; i <= ofs_end; i++, val++) {
		lis2dh_convert(lis2dh->sample.xyz[i], lis2dh->scale, val);
	}

	return 0;
}

static int lis2dh_sample_fetch(const struct device *dev,
			       enum sensor_channel chan)
{
	struct lis2dh_data *lis2dh = dev->data;
	size_t i;
	int ret;

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL ||
			chan == SENSOR_CHAN_ACCEL_XYZ);

	/*
	 * since status and all accel data register addresses are consecutive,
	 * a burst read can be used to read all the samples
	 */
	ret = lis2dh->hw_tf->read_data(dev, LIS2DH_REG_STATUS,
					  lis2dh->sample.raw,
					  sizeof(lis2dh->sample.raw));
	if (unlikely(ret < 0)) {
		LOG_WRN("Could not read accel axis data");
		return ret;
	}

	for (i = 0; i < (3 * sizeof(int16_t)); i += sizeof(int16_t)) {
		int16_t *sample = (int16_t *)&lis2dh->sample.raw[1 + i];

		*sample = sys_le16_to_cpu(*sample);
	}

	if (lis2dh->sample.status & LIS2DH_STATUS_DRDY_MASK) {
		return 0;
	}

	return -ENODATA;
}

#if defined(CONFIG_LIS2DH_ODR_RUNTIME)
/* 1620 & 5376 are low power only */
static const uint16_t lis2dh_odr_map[] = {0, 1, 10, 25, 50, 100, 200, 400, 1620,
				       1344, 5376};

static int lis2dh_freq_to_odr_val(uint16_t freq)
{
	size_t i;

	/* An ODR of 0Hz is not allowed */
	if (freq == 0U) {
		LOG_ERR("An ODR of 0Hz is not allowed, use the PM subsystem\
		 or lis2dh_suspend() instead");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(lis2dh_odr_map); i++) {
		if (freq == lis2dh_odr_map[i]) {
			return i;
		}
	}
	return -EINVAL;
}

static int lis2dh_acc_odr_set(const struct device *dev, uint16_t freq)
{
	int odr;
	int ret;
	uint8_t value;
	struct lis2dh_data *lis2dh = dev->data;

	odr = lis2dh_freq_to_odr_val(freq);
	if (unlikely(odr < 0)) {
		return odr;
	}


	ret = lis2dh->hw_tf->read_reg(dev, LIS2DH_REG_CTRL1, &value);
	if (unlikely(ret < 0)) {
		return ret;
	}

	/* some odr values cannot be set in certain power modes */
	if ((value & LIS2DH_LP_EN_BIT_MASK) == 0U && odr == LIS2DH_ODR_8) {
		return -ENOTSUP;
	}

	/* adjust odr index for LP enabled mode, see table above */
	if (((value & LIS2DH_LP_EN_BIT_MASK) == LIS2DH_LP_EN_BIT_MASK) &&
		(odr == LIS2DH_ODR_9 + 1)) {
		odr--;
	}

	/* store last set freq value so it can be restored */
	if (freq != lis2dh->target_odr) {
		lis2dh->target_odr = odr;
		LOG_DBG("set target odr to %i", lis2dh->target_odr);
	}

	/* If sensor is powered down only set the target frequency 
	 * but don't apply it to hardware, re-enabling the sensor
	 * with lis2dh_power_down() will do that.
	 */
#if defined(CONFIG_PM_DEVICE)
	if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
		LOG_INF("New ODR value will be applied once the sensor enters active mode.");
		return 0;
	}
#endif
	return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL1,
				      (value & ~LIS2DH_ODR_MASK) |
				      LIS2DH_ODR_RATE(odr));
}
#endif

#if (defined(CONFIG_LIS2DH_OPER_MODE_RUNTIME) || defined(CONFIG_LIS2DH_OPER_MODE_HIGH_RES))
static int lis2dh_set_high_res(const struct device *dev, bool enable)
{
	struct lis2dh_data *lis2dh = dev->data;
	int ret;
	uint8_t value;

	if (enable) {
		/* re-enable High resolution mode */
		ret = lis2dh->hw_tf->read_reg(dev, LIS2DH_REG_CTRL4, &value);
		if (unlikely(ret < 0)) {
			return ret;
		}
		return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL4, value | LIS2DH_HR_BIT);
	} else { /* disable */
		ret = lis2dh->hw_tf->read_reg(dev, LIS2DH_REG_CTRL4, &value);
		if (unlikely(ret < 0)) {
			return ret;
		}
		return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL4, value & ~LIS2DH_POWER_DOWN);
	}
}
#endif /* CONFIG_LIS2DH_OPER_MODE_RUNTIME || CONFIG_LIS2DH_OPER_MODE_HIGH_RES */

#if defined(CONFIG_LIS2DH_OPER_MODE_RUNTIME)
int lis2dh_set_oper_mode(const struct device *dev, enum lis2dh_oper_mode new_mode)
{
	struct lis2dh_data *lis2dh = dev->data;
	int ret;

	if (new_mode == lis2dh->oper_mode){
		return 0;
	}

	LOG_INF("New oper mode: %i", (uint8_t)new_mode);

#if defined(CONFIG_PM_DEVICE)
	if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
		lis2dh->oper_mode = new_mode;
		LOG_INF("New operation mode will be applied once the sensor enters active mode.");
		return 0;
	}
#endif

	if (new_mode == OPER_MODE_LOW_POWER){
		if (lis2dh->oper_mode == OPER_MODE_HIGH_RES) {
			ret = lis2dh_set_high_res(dev, false);
			if (unlikely(ret < 0)) {
				return ret;
			}
		}
		ret = lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
									(uint8_t)LIS2DH_LP_EN_BIT_MASK,
									(uint8_t)LIS2DH_LP_EN_BIT);
		if (unlikely(ret < 0)){
			return ret;
		}
		lis2dh->oper_mode = OPER_MODE_LOW_POWER;
		return ret;

	} else if (new_mode == OPER_MODE_NORMAL) {
		if (lis2dh->oper_mode == OPER_MODE_HIGH_RES) {
			ret = lis2dh_set_high_res(dev, false);
			if (unlikely(ret < 0)) {
				return ret;
			}
		}
		ret = lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
									(uint8_t)LIS2DH_LP_EN_BIT_MASK,
								   ~(uint8_t)LIS2DH_LP_EN_BIT);
		if (unlikely(ret < 0)){
			return ret;
		}
		lis2dh->oper_mode = OPER_MODE_NORMAL;
		return ret;

	} else if (new_mode == OPER_MODE_HIGH_RES) {
		if (lis2dh->oper_mode == OPER_MODE_LOW_POWER){
			ret = lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										(uint8_t)LIS2DH_LP_EN_BIT_MASK,
									   ~(uint8_t)LIS2DH_LP_EN_BIT);
			if (unlikely(ret < 0)){
				return ret;
			}
		}
		ret = lis2dh_set_high_res(dev, true);
		if (unlikely(ret < 0)){
			return ret;
		}
		lis2dh->oper_mode = OPER_MODE_HIGH_RES;
		return ret;

	} else {
		return -EINVAL;
	}
}
#endif

#if defined(CONFIG_PM_DEVICE)
static int lis2dh_suspend(const struct device *dev)
{
	struct lis2dh_data *lis2dh = dev->data;
	if (lis2dh->pm_state == PM_DEVICE_STATE_ACTIVE) {
#if defined(CONFIG_LIS2DH_OPER_MODE_HIGH_RES)
		lis2dh_set_high_res(dev, false);
#endif
		/* set ODR to 0, Enable Low Power and disable all axis */
		return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL1, LIS2DH_POWER_DOWN);
	} else {
		LOG_INF("sensor already powered down");
		return 0;
	} 
}

static int lis2dh_resume_from_suspend(const struct device *dev)
{
	struct lis2dh_data *lis2dh = dev->data;

	if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
		
		uint8_t axes = 0;
		uint8_t oper_mode = 0;
#if defined(CONFIG_LIS2DH_AXES_RUNTIME)
		if (lis2dh->target_X_axis) {
			axes |= (uint8_t)LIS2DH_ACCEL_X_EN_BIT;
		}
		if (lis2dh->target_Y_axis) {
			axes |= (uint8_t)LIS2DH_ACCEL_Y_EN_BIT;
		}
		if (lis2dh->target_Z_axis) {
			axes |= (uint8_t)LIS2DH_ACCEL_Z_EN_BIT;
		}
#else
		axes = (uint8_t)LIS2DH_ACCEL_EN_BITS;
#endif /* CONFIG_LIS2DH_AXES_RUNTIME */	

#if defined(CONFIG_LIS2D_OPER_MODE_RUNTIME)
		if (lis2dh->oper_mode == OPER_MODE_LOW_POWER) {
			oper_mode |= LIS2DH_LP_EN_BIT;
		} else if (lis2dh->oper_mode == OPER_MODE_HIGH_RES) {
			int ret = lis2dh_set_high_res(dev, true);
			if (unlikely(ret < 0)){
				return ret;
			}
		} 
#elif defined(CONFIG_LIS2DH_OPER_MODE_HIGH_RES)
		/* re-enable High resolution mode */
		int ret = lis2dh_set_high_res(dev, true);
		if (unlikely(ret < 0)){
			return ret;
		}
#elif defined(CONFIG_LIS2DH_OPER_MODE_LOW_POWER)
		oper_mode |= LIS2DH_LP_EN_BIT;
#endif /* CONFIG_LIS2DH_OPER_MODE */

#if defined(CONFIG_LIS2DH_ODR_RUNTIME)
		uint8_t odr = (uint8_t)LIS2DH_ODR_RATE(lis2dh->target_odr);
#else
		uint8_t odr = (uint8_t)LIS2DH_ODR_BITS;
#endif /* CONFIG_LIS2DH_ODR_RUNTIME */
		return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL1,\
							axes | oper_mode | odr);									
	} else {
		LOG_INF("sensor is not powered down");
		return 0;
	}
}

static int lis2dh_get_power_state(const struct device *dev)
{
	struct lis2dh_data *lis2dh = dev->data;
	return lis2dh->pm_state;
}
#endif /* CONFIG_PM_DEVICE */

#if defined(CONFIG_LIS2DH_ACCEL_RANGE_RUNTIME)

#define LIS2DH_RANGE_IDX_TO_VALUE(idx)		(1 << ((idx) + 1))
#define LIS2DH_NUM_RANGES			4

static int lis2dh_range_to_reg_val(uint16_t range)
{
	int i;

	for (i = 0; i < LIS2DH_NUM_RANGES; i++) {
		if (range == LIS2DH_RANGE_IDX_TO_VALUE(i)) {
			return i;
		}
	}

	return -EINVAL;
}

static int lis2dh_acc_range_set(const struct device *dev, int32_t range)
{
	struct lis2dh_data *lis2dh = dev->data;
	int fs;

	fs = lis2dh_range_to_reg_val(range);
	if (fs < 0) {
		return fs;
	}

	lis2dh->scale = lis2dh_reg_val_to_scale[fs];

	return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL4,
					 LIS2DH_FS_MASK,
					 (fs << LIS2DH_FS_SHIFT));
}
#endif

int lis2dh_acc_act_config(const struct device *dev,
			    enum sensor_attribute attr,
			    const struct sensor_value *val)
{
	struct lis2dh_data *lis2dh = dev->data;
	int ret;

	if ((uint16_t)attr == SENSOR_ATTR_LIS2DH_ACT_TH) {
		uint8_t range_g, reg_val;
		uint32_t act_th_ums2;

		ret = lis2dh->hw_tf->read_reg(dev, LIS2DH_REG_CTRL4,
						 &reg_val);
		if (ret < 0) {
			return ret;
		}

		/* fs reg value is in the range 0 (2g) - 3 (16g) */
		range_g = 2 * (1 << ((LIS2DH_FS_MASK & reg_val)
				      >> LIS2DH_FS_SHIFT));

		act_th_ums2 = val->val1 * 1000000 + val->val2;

		/* make sure the provided threshold does not exceed range */
		if ((act_th_ums2 - 1) > (range_g * SENSOR_G)) {
			return -EINVAL;
		}

		/* 7 bit full range value */
		reg_val = 128 / range_g * (act_th_ums2 - 1) / SENSOR_G;

		LOG_INF("act_ths=0x%x range_g=%d ums2=%u", reg_val,
			    range_g, act_th_ums2 - 1);

		return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_ACT_THS,
						  reg_val);
	} else { /* SENSOR_ATTR_LIS2DH_ACT_DUR */
		/*
		 * slope duration is measured in number of samples:
		 * N/ODR where N is the register value
		 */
		if (val->val1 < 0 || val->val1 > 127) {
			return -ENOTSUP;
		}

		LOG_INF("act_dur=0x%x", val->val1);

		return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_ACT_DUR,
						  val->val1);
	}
}

static int lis2dh_acc_config(const struct device *dev,
			     enum sensor_channel chan,
			     enum sensor_attribute attr,
			     const struct sensor_value *val)
{
	switch ((uint16_t)attr) {
#if defined(CONFIG_LIS2DH_ACCEL_RANGE_RUNTIME)
	case SENSOR_ATTR_FULL_SCALE:
		return lis2dh_acc_range_set(dev, sensor_ms2_to_g(val));
#endif
#if defined(CONFIG_LIS2DH_ODR_RUNTIME)
	case SENSOR_ATTR_SAMPLING_FREQUENCY:
		return lis2dh_acc_odr_set(dev, val->val1);
#endif
#if defined(CONFIG_LIS2DH_TRIGGER)
	case SENSOR_ATTR_SLOPE_TH:
	case SENSOR_ATTR_SLOPE_DUR:
		return lis2dh_acc_slope_config(dev, attr, val);
#endif
	case SENSOR_ATTR_LIS2DH_ACT_TH:
	case SENSOR_ATTR_LIS2DH_ACT_DUR:
		return lis2dh_acc_act_config(dev, attr, val);
	default:
		LOG_DBG("Accel attribute not supported.");
		return -ENOTSUP;
	}

	return 0;
}

#if	defined(CONFIG_LIS2DH_AXES_RUNTIME)
int lis2dh_axis_set(const struct device *dev, enum sensor_channel chan, bool enable)
{
	struct lis2dh_data *lis2dh = dev->data;
	switch (chan) {
	case SENSOR_CHAN_ACCEL_X:
		if (enable) {
			lis2dh->target_X_axis = true;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Enabled X axis");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_X_EN_BIT,
										 (uint8_t)LIS2DH_ACCEL_X_EN_BIT);
		} else { /* disable */
			lis2dh->target_X_axis = false;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Disabled X axis");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_X_EN_BIT,
										~(uint8_t)LIS2DH_ACCEL_X_EN_BIT);
		}
	case SENSOR_CHAN_ACCEL_Y:
		if (enable) {
			lis2dh->target_Y_axis = true;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Enabled Y axis");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_Y_EN_BIT,
										 (uint8_t)LIS2DH_ACCEL_Y_EN_BIT);
		} else { /* disable */
			lis2dh->target_Y_axis = false;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Disabled Y axis");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_Y_EN_BIT,
										~(uint8_t)LIS2DH_ACCEL_Y_EN_BIT);
		}
	case SENSOR_CHAN_ACCEL_Z:
		if (enable) {
			lis2dh->target_Z_axis = true;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Enabled Z axis");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_Z_EN_BIT,
										 (uint8_t)LIS2DH_ACCEL_Z_EN_BIT);
		} else { /* disable */
			lis2dh->target_Z_axis = false;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Disabled Z axis");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_Z_EN_BIT,
										~(uint8_t)LIS2DH_ACCEL_Z_EN_BIT);
		}
	case SENSOR_CHAN_ACCEL_XYZ:
		if (enable) {
			lis2dh->target_X_axis = true;
			lis2dh->target_Y_axis = true;
			lis2dh->target_Z_axis = true;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Enabled X, Y and Z axes");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_XYZ_BITS,
										 (uint8_t)LIS2DH_ACCEL_XYZ_BITS);
		} else { /* disable */
			lis2dh->target_X_axis = false;
			lis2dh->target_Y_axis = false;
			lis2dh->target_Z_axis = false;
#if defined(CONFIG_PM_DEVICE)
			if (lis2dh->pm_state == PM_DEVICE_STATE_LOW_POWER) {
				goto lis2dh_axis_end;
			}
#endif
			LOG_INF("Disabled X, Y and Z axes");
			return lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL1,
										 (uint8_t)LIS2DH_ACCEL_XYZ_BITS,
										~(uint8_t)LIS2DH_ACCEL_XYZ_BITS);
		}
	default:
		LOG_WRN("lis2dh_axis_set() not supported on this channel.");
		return -ENOTSUP;
	}
#if defined(CONFIG_PM_DEVICE)
	lis2dh_axis_end:
	LOG_INF("New axis settings will be applied once the sensor leaves power down mode.");
#endif
	return 0;
}

bool lis2dh_axis_get(const struct device *dev, enum sensor_channel chan)
{
	struct lis2dh_data *lis2dh = dev->data;
	uint8_t value;
	int ret;

	ret = lis2dh->hw_tf->read_reg(dev, LIS2DH_REG_CTRL1, &value);
	if (unlikely(ret < 0)) {
		return ret;
	}

	switch (chan) {
		case SENSOR_CHAN_ACCEL_X:
			if (value & LIS2DH_ACCEL_X_EN_BIT) {
				return true;
			} else {
				return false;
			}
		case SENSOR_CHAN_ACCEL_Y:
		if (value & LIS2DH_ACCEL_Y_EN_BIT) {
				return true;
			} else {
				return false;
			}
		case SENSOR_CHAN_ACCEL_Z:
			if (value & LIS2DH_ACCEL_Z_EN_BIT) {
				return true;
			} else {
				return false;
			}
		case SENSOR_CHAN_ACCEL_XYZ:
			LOG_WRN("lis2dh_axis_get() can't read multiple axes simultaniously.");
			return -ENOTSUP;
		default:
			LOG_WRN("lis2dh_axis_get() not supported on this channel.");
			return -ENOTSUP;
	}
}
#endif /* CONFIG_LIS2DH_AXES_RUNTIME */

static int lis2dh_attr_set(const struct device *dev, enum sensor_channel chan,
			   enum sensor_attribute attr,
			   const struct sensor_value *val)
{
	switch (chan) {
	case SENSOR_CHAN_ACCEL_X:
	case SENSOR_CHAN_ACCEL_Y:
	case SENSOR_CHAN_ACCEL_Z:
	case SENSOR_CHAN_ACCEL_XYZ:
		return lis2dh_acc_config(dev, chan, attr, val);
	default:
		LOG_WRN("attr_set() not supported on this channel.");
		return -ENOTSUP;
	}

	return 0;
}

static const struct sensor_driver_api lis2dh_driver_api = {
	.attr_set = lis2dh_attr_set,
#if CONFIG_LIS2DH_TRIGGER
	.trigger_set = lis2dh_trigger_set,
#endif
	.sample_fetch = lis2dh_sample_fetch,
	.channel_get = lis2dh_channel_get,
};

int lis2dh_reg_init(const struct device *dev)
{
	struct lis2dh_data *lis2dh = dev->data;
	const struct lis2dh_config *cfg = dev->config;
	int ret;
	uint8_t ctrl_raw[6];
	uint8_t act_raw[2];
	/* Initialize control register ctrl1 to ctrl 6 to default boot values
	 * to avoid warm start/reset issues as the accelerometer has no reset
	 * pin. Register values are retained if power is not removed.
	 * Default values see LIS2DH documentation page 30, chapter 6.
	 */ 
	(void)memset(ctrl_raw, 0, sizeof(ctrl_raw));
	ctrl_raw[0] = LIS2DH_ACCEL_EN_BITS;

	ret = lis2dh->hw_tf->write_data(dev, LIS2DH_REG_CTRL1, ctrl_raw,
						sizeof(ctrl_raw));
	if (unlikely(ret < 0)) {
		LOG_ERR("Failed to reset ctrl registers.");
		return ret;
	}

	/* Reset ACT registers */
	(void)memset(act_raw, 0, sizeof(act_raw));
	ret = lis2dh->hw_tf->write_data(dev, LIS2DH_REG_ACT_THS, act_raw,
						sizeof(act_raw));
	if (unlikely(ret < 0)) {
		LOG_ERR("Failed to reset ACT registers.");
		return ret;
	}
	uint8_t high_res = 0;
#if defined(CONFIG_LIS2DH_OPER_MODE_HIGH_RES)
	high_res |= LIS2DH_HR_BIT;
#endif
	/* set full scale range and store it for later conversion */
	lis2dh->scale = lis2dh_reg_val_to_scale[LIS2DH_FS_IDX];
	ret = lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL4,
					LIS2DH_FS_BITS | high_res);
	if (unlikely(ret < 0)) {
		LOG_ERR("Failed to set full scale ctrl register.");
		return ret;
	}

#if defined(CONFIG_LIS2DH_TRIGGER)
	if (cfg->gpio_drdy.port != NULL || cfg->gpio_int.port != NULL) {
		ret = lis2dh_init_interrupt(dev);
		if (unlikely(ret < 0)) {
			LOG_ERR("Failed to initialize interrupts.");
			return ret;
		}
	}
#endif

	LOG_INF("bus=%s fs=%d, odr=0x%x lp_en=0x%x scale=%d",
		    cfg->bus_name, 1 << (LIS2DH_FS_IDX + 1),
		    LIS2DH_ODR_IDX, (uint8_t)LIS2DH_LP_EN_BIT, lis2dh->scale);
#if defined(CONFIG_PM_DEVICE)
	/* set pm_state as active */
	lis2dh->pm_state = PM_DEVICE_STATE_ACTIVE;
#endif
#if defined(CONFIG_LIS2DH_OPER_MODE_RUNTIME)
	/* set target oper mode to normal */
	lis2dh->oper_mode = OPER_MODE_NORMAL;
#endif
#if defined(CONFIG_LIS2DH_AXES_RUNTIME)
	/* set all axes as enabled */
	lis2dh->target_X_axis = true;
	lis2dh->target_Y_axis = true;
	lis2dh->target_Z_axis = true;
#endif
	/* enable accel measurements and set power mode and data rate */
	return lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL1,
					LIS2DH_ACCEL_EN_BITS | LIS2DH_ODR_BITS);
}

int lis2dh_init(const struct device *dev)
{
	struct lis2dh_data *lis2dh = dev->data;
	const struct lis2dh_config *cfg = dev->config;
	int ret;
	uint8_t id;

	lis2dh->bus = device_get_binding(cfg->bus_name);
	if (!lis2dh->bus) {
		LOG_ERR("master not found: %s", cfg->bus_name);
		return -EINVAL;
	}

	cfg->bus_init(dev);

	ret = lis2dh->hw_tf->read_reg(dev, LIS2DH_REG_WAI, &id);
	if (unlikely(ret < 0)) {
		LOG_ERR("Failed to read chip id.");
		return ret;
	}

	if (id != LIS2DH_CHIP_ID) {
		LOG_ERR("Invalid chip ID: %02x\n", id);
		return -EINVAL;
	}

	/* Fix LSM303AGR_ACCEL device scale values */
	if (cfg->is_lsm303agr_dev) {
		lis2dh_reg_val_to_scale[0] = ACCEL_SCALE(1563);
		lis2dh_reg_val_to_scale[1] = ACCEL_SCALE(3126);
		lis2dh_reg_val_to_scale[2] = ACCEL_SCALE(6252);
		lis2dh_reg_val_to_scale[3] = ACCEL_SCALE(18758);
	}

	if (cfg->disc_pull_up) {
		ret = lis2dh->hw_tf->update_reg(dev, LIS2DH_REG_CTRL0,
						   LIS2DH_SDO_PU_DISC_MASK,
						   LIS2DH_SDO_PU_DISC_MASK);
		if (ret < 0) {
			LOG_ERR("Failed to disconnect SDO/SA0 pull-up.");
			return ret;
		}
	}

#if	defined(CONFIG_LIS2DH_AXES_RUNTIME)
	lis2dh->target_X_axis = true;
	lis2dh->target_Y_axis = true;
	lis2dh->target_Z_axis = true;
#endif

	return lis2dh_reg_init(dev);
}

int lis2dh_reset(const struct device *dev)
{
	struct lis2dh_data *lis2dh = dev->data;
	int ret;

	ret = lis2dh->hw_tf->write_reg(dev, LIS2DH_REG_CTRL5,
					(uint8_t)LIS2DH_REBOOT_BIT);
	if (unlikely(ret < 0)) {
		LOG_ERR("Failed to reset Lis2dh");
		return ret;
	}

	LOG_DBG("Lis2dh has been reset, reinitialising...");

	return lis2dh_reg_init(dev);
}

#if defined(CONFIG_PM_DEVICE)
static int lis2dh_pm_control(const struct device *dev, uint32_t ctrl_command,
			      uint32_t *state, pm_device_cb cb, void *arg)
{
	int ret = 0;
	struct lis2dh_data *lis2dh = dev->data;

	switch (ctrl_command) {
	case PM_DEVICE_STATE_SET:
		if (*((uint32_t*)state) == PM_DEVICE_STATE_ACTIVE) {
			ret = lis2dh_resume_from_suspend(dev);
			if (ret < 0) {
				return ret;
			}
			lis2dh->pm_state = PM_DEVICE_STATE_ACTIVE;
		} else {
			ret = lis2dh_suspend(dev);
			if (ret < 0) {
				return ret;
			}
			lis2dh->pm_state = PM_DEVICE_STATE_LOW_POWER;
		}
		break;
	case PM_DEVICE_STATE_GET:
		*state = lis2dh_get_power_state(dev);
		break;
	default:
		ret = -EINVAL;
	}

	if (cb) {
		cb(dev, ret, state, arg);
	}

	return ret;
}
#endif /* CONFIG_PM_DEVICE */

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "LIS2DH driver enabled without any devices"
#endif

/*
 * Device creation macro, shared by LIS2DH_DEFINE_SPI() and
 * LIS2DH_DEFINE_I2C().
 */

#define LIS2DH_DEVICE_INIT(inst)					\
	DEVICE_DT_INST_DEFINE(inst,					\
			    lis2dh_init,				\
			    lis2dh_pm_control,					\
			    &lis2dh_data_##inst,			\
			    &lis2dh_config_##inst,			\
			    POST_KERNEL,				\
			    CONFIG_SENSOR_INIT_PRIORITY,		\
			    &lis2dh_driver_api);

#define IS_LSM303AGR_DEV(inst) \
	DT_NODE_HAS_COMPAT(DT_DRV_INST(inst), st_lsm303agr_accel)

#define DISC_PULL_UP(inst) \
	DT_INST_PROP(inst, disconnect_sdo_sa0_pull_up)

/*
 * Instantiation macros used when a device is on a SPI bus.
 */

#define LIS2DH_HAS_CS(inst) DT_INST_SPI_DEV_HAS_CS_GPIOS(inst)

#define LIS2DH_DATA_SPI_CS(inst)					\
	{ .cs_ctrl = {							\
		.gpio_pin = DT_INST_SPI_DEV_CS_GPIOS_PIN(inst),		\
		.gpio_dt_flags = DT_INST_SPI_DEV_CS_GPIOS_FLAGS(inst),	\
		},							\
	}

#define LIS2DH_DATA_SPI(inst)						\
	COND_CODE_1(LIS2DH_HAS_CS(inst),				\
		    (LIS2DH_DATA_SPI_CS(inst)),				\
		    ({}))

#define LIS2DH_SPI_CS_PTR(inst)						\
	COND_CODE_1(LIS2DH_HAS_CS(inst),				\
		    (&(lis2dh_data_##inst.cs_ctrl)),			\
		    (NULL))

#define LIS2DH_SPI_CS_LABEL(inst)					\
	COND_CODE_1(LIS2DH_HAS_CS(inst),				\
		    (DT_INST_SPI_DEV_CS_GPIOS_LABEL(inst)), (NULL))

#define LIS2DH_SPI_CFG(inst)						\
	(&(struct lis2dh_spi_cfg) {					\
		.spi_conf = {						\
			.frequency =					\
				DT_INST_PROP(inst, spi_max_frequency),	\
			.operation = (SPI_WORD_SET(8) |			\
				      SPI_OP_MODE_MASTER |		\
				      SPI_MODE_CPOL |			\
				      SPI_MODE_CPHA),			\
			.slave = DT_INST_REG_ADDR(inst),		\
			.cs = LIS2DH_SPI_CS_PTR(inst),			\
		},							\
		.cs_gpios_label = LIS2DH_SPI_CS_LABEL(inst),		\
	})

#if defined(CONFIG_LIS2DH_TRIGGER)
#define GPIO_DT_SPEC_INST_GET_BY_IDX_COND(id, prop, idx)		\
	COND_CODE_1(DT_INST_PROP_HAS_IDX(id, prop, idx),		\
		    (GPIO_DT_SPEC_INST_GET_BY_IDX(id, prop, idx)),	\
		    ({.port = NULL, .pin = 0, .dt_flags = 0}))

#define LIS2DH_CFG_INT(inst) \
	.gpio_drdy =							\
	    GPIO_DT_SPEC_INST_GET_BY_IDX_COND(inst, irq_gpios, 0),	\
	.gpio_int =							\
	    GPIO_DT_SPEC_INST_GET_BY_IDX_COND(inst, irq_gpios, 1),
#else
#define LIS2DH_CFG_INT(inst)
#endif /* CONFIG_LIS2DH_TRIGGER */

#define LIS2DH_CONFIG_SPI(inst)						\
	{								\
		.bus_name = DT_INST_BUS_LABEL(inst),			\
		.bus_init = lis2dh_spi_init,				\
		.bus_cfg = { .spi_cfg = LIS2DH_SPI_CFG(inst)	},	\
		.is_lsm303agr_dev = IS_LSM303AGR_DEV(inst),		\
		.disc_pull_up = DISC_PULL_UP(inst),			\
		LIS2DH_CFG_INT(inst)					\
	}

#define LIS2DH_DEFINE_SPI(inst)						\
	static struct lis2dh_data lis2dh_data_##inst =			\
		LIS2DH_DATA_SPI(inst);					\
	static const struct lis2dh_config lis2dh_config_##inst =	\
		LIS2DH_CONFIG_SPI(inst);				\
	LIS2DH_DEVICE_INIT(inst)

/*
 * Instantiation macros used when a device is on an I2C bus.
 */

#define LIS2DH_CONFIG_I2C(inst)						\
	{								\
		.bus_name = DT_INST_BUS_LABEL(inst),			\
		.bus_init = lis2dh_i2c_init,				\
		.bus_cfg = { .i2c_slv_addr = DT_INST_REG_ADDR(inst), },	\
		.is_lsm303agr_dev = IS_LSM303AGR_DEV(inst),		\
		.disc_pull_up = DISC_PULL_UP(inst),			\
		LIS2DH_CFG_INT(inst)					\
	}

#define LIS2DH_DEFINE_I2C(inst)						\
	static struct lis2dh_data lis2dh_data_##inst;			\
	static const struct lis2dh_config lis2dh_config_##inst =	\
		LIS2DH_CONFIG_I2C(inst);				\
	LIS2DH_DEVICE_INIT(inst)
/*
 * Main instantiation macro. Use of COND_CODE_1() selects the right
 * bus-specific macro at preprocessor time.
 */

#define LIS2DH_DEFINE(inst)						\
	COND_CODE_1(DT_INST_ON_BUS(inst, spi),				\
		    (LIS2DH_DEFINE_SPI(inst)),				\
		    (LIS2DH_DEFINE_I2C(inst)))

DT_INST_FOREACH_STATUS_OKAY(LIS2DH_DEFINE)
