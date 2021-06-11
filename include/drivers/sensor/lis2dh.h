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
 * @brief Put the sensor in powered-down mode
 *
 * @param dev Pointer to the sensor device
 * @param power_down Boolean value whether the device should be powered down
 * @return 0 if successful, negative errno code if failure.
 */
int lis2dh_power_down(const struct device *dev, bool power_down);

/**
 * @brief put the sensor 
 *
 * @param dev Pointer to the sensor device
 * @return 0 if successful, negative errno code if failure.
 */
int lis2dh_reset(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_SENSOR_LIS2DH_H_ */