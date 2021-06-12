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

/**
 * @brief Put the sensor in powered-down mode.
 *
 * @param dev Pointer to the sensor device
 * @param power_down Boolean value whether the device should be powered down.
 * @return 0 if successful, negative errno code if failure.
 */
int lis2dh_power_down_set(const struct device *dev, bool power_down);

/**
 * @brief Get the sensors powered-down state.
 *
 * @param dev Pointer to the sensor device
 * @return true if power down mode is enabled, false if not powered down.
 */
bool lis2dh_power_down_get(const struct device *dev);

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

/**
 * @brief Get the state of a specific axis
 *
 * @param dev Pointer to the sensor device.
 * @param chan Which axis to enable or disable.
 * @return true if axis is enabled, false if disabled.
 */
bool lis2dh_axis_get(const struct device *dev, enum sensor_channel chan);
#endif /* CONFIG_LIS2DH_AXES_RUNTIME*/

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_SENSOR_LIS2DH_H_ */