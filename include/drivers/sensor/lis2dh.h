/*
 * Copyright (c) 2021 
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Extended public API for the lis2dh accelerometer 
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_SENSOR_LIS2DH_H_
#define ZEPHYR_INCLUDE_DRIVERS_SENSOR_LIS2DH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <drivers/sensor.h>

enum sensor_attribute_lis2dh {
	/* Lis2dh activity threshold */
	SENSOR_ATTR_LIS2DH_ACT_TH = SENSOR_ATTR_PRIV_START,
	/* Lis2dh activity threshold duration */
	SENSOR_ATTR_LIS2DH_ACT_DUR,
};

#ifdef CONFIG_LIS2DH_OPER_MODE_RUNTIME
enum lis2dh_oper_mode {
	OPER_MODE_LOW_POWER,
	OPER_MODE_NORMAL,
	OPER_MODE_HIGH_RES,
};
#endif

/**
 * @brief reset the sensors registers.
 *
 * @param dev Pointer to the sensor device.
 * @return 0 if successful, negative errno code if failure.
 */
int lis2dh_reset(const struct device *dev);

#if defined(CONFIG_LIS2DH_AXES_RUNTIME)
/**
 * @brief Enable or disable axes
 *
 * @param dev Pointer to the sensor device.
 * @param chan Which axis to enable or disable.
 * @param enable Bool whether the selected axes should be anabled or disabled.
 * @return 0 if successful, negative errno code if failure.
 */
int lis2dh_axis_set(const struct device *dev, enum sensor_channel chan, bool enable);
#endif /* CONFIG_LIS2DH_AXES_RUNTIME*/

#ifdef CONFIG_LIS2DH_OPER_MODE_RUNTIME
/**
 * @brief Select operation mode
 *
 * @param dev Pointer to the sensor device.
 * @param new_mode The new mode to be set
 * @return 0 if successful, negative errno code if failure.
 */
int lis2dh_set_oper_mode(const struct device *dev, enum lis2dh_oper_mode new_mode);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_SENSOR_LIS2DH_H_ */