#include <kernel.h>
#include <drivers/sensor.h>
#include <init.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>

#include <logging/log.h>

#include "cmps03.h"

LOG_MODULE_REGISTER(CMPS03, CONFIG_SENSOR_LOG_LEVEL);

#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0
#warning "CMPS03 driver enabled without any devices."
#endif

struct cmps03_data {
	const struct device *i2c_master;

	uint16_t cmps_val;
};

struct cmps03_config {
	const struct device *bus;
	const struct cmps03_bus_io *bus_io;
	const union cmps03_bus_config bus_config;
};

static inline struct cmps03_data *to_data(const struct device *dev)
{
	return dev->data;
}

static inline const struct cmps03_config *to_config(const struct device *dev)
{
	return dev->config;
}

static inline const struct device *to_bus(const struct device *dev)
{
	return to_config(dev)->bus;
}

static inline const union cmps03_bus_config*
to_bus_config(const struct device *dev)
{
	return &to_config(dev)->bus_config;
}

static inline int cmps03_bus_check(const struct device *dev)
{
	return to_config(dev)->bus_io->check(to_bus(dev), to_bus_config(dev));
}

static inline int cmps03_reg_read(const struct device *dev,
				  uint8_t start, uint8_t *buf, int size)
{
	return to_config(dev)->bus_io->read(to_bus(dev), to_bus_config(dev),
					    start, buf, size);
}

static inline int cmps03_reg_write(const struct device *dev, uint8_t reg,
				   uint8_t val)
{
	return to_config(dev)->bus_io->write(to_bus(dev), to_bus_config(dev),
					     reg, val);
}

static int cmps03_sample_fetch(const struct device *dev,
			       enum sensor_channel chan)
{
	struct cmps03_data *data = to_data(dev);
	uint8_t buf[8];
	int32_t adc_press, adc_temp, adc_humidity;
	int size = 6;
	int ret;

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL);

	ret = cmps03_reg_read(dev, CMPS03_REG_PRESS_MSB, buf, size);
	if (ret < 0) {
		return ret;
	}

	adc_press = (buf[0] << 12) | (buf[1] << 4) | (buf[2] >> 4);
	adc_temp = (buf[3] << 12) | (buf[4] << 4) | (buf[5] >> 4);

	cmps03_compensate_temp(data, adc_temp);
	cmps03_compensate_press(data, adc_press);

	return 0;
}

static int cmps03_channel_get(const struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct cmps03_data *data = to_data(dev);

	return 0;
}

static const struct sensor_driver_api cmps03_api_funcs = {
	.sample_fetch = cmps03_sample_fetch,
	.channel_get = cmps03_channel_get,
};

static int cmps03_chip_init(const struct device *dev)
{
	struct cmps03_data *data = to_data(dev);
	int err;

	// LOG_DBG("initializing \"%s\" on bus \"%s\"",
	// 	dev->name, to_bus(dev)->name);

	// err = cmps03_bus_check(dev);
	// if (err < 0) {
	// 	LOG_DBG("bus check failed: %d", err);
	// 	return err;
	// }

	// err = cmps03_reg_read(dev, CMPS03_REG_ID, &data->chip_id, 1);
	// if (err < 0) {
	// 	LOG_DBG("ID read failed: %d", err);
	// 	return err;
	// }

	// if (data->chip_id == CMPS03_CHIP_ID) {
	// 	LOG_DBG("ID OK");
	// } else if (data->chip_id == BMP280_CHIP_ID_MP ||
	// 	   data->chip_id == BMP280_CHIP_ID_SAMPLE_1) {
	// 	LOG_DBG("ID OK (BMP280)");
	// } else {
	// 	LOG_DBG("bad chip id 0x%x", data->chip_id);
	// 	return -ENOTSUP;
	// }

	// err = cmps03_read_compensation(dev);
	// if (err < 0) {
	// 	return err;
	// }

	// if (data->chip_id == CMPS03_CHIP_ID) {
	// 	err = cmps03_reg_write(dev, CMPS03_REG_CTRL_HUM,
	// 			       CMPS03_HUMIDITY_OVER);
	// 	if (err < 0) {
	// 		LOG_DBG("CTRL_HUM write failed: %d", err);
	// 		return err;
	// 	}
	// }

	// err = cmps03_reg_write(dev, CMPS03_REG_CTRL_MEAS,
	// 		       CMPS03_CTRL_MEAS_VAL);
	// if (err < 0) {
	// 	LOG_DBG("CTRL_MEAS write failed: %d", err);
	// 	return err;
	// }

	// err = cmps03_reg_write(dev, CMPS03_REG_CONFIG,
	// 		       CMPS03_CONFIG_VAL);
	// if (err < 0) {
	// 	LOG_DBG("CONFIG write failed: %d", err);
	// 	return err;
	// }

	// return 0;
}