/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <drivers/sensor/lis2dh.h>

static void fetch_and_display(const struct device *sensor)
{
	static unsigned int count;
	struct sensor_value accel[3];
	const char *overrun = "";
	int rc = sensor_sample_fetch(sensor);

	++count;
	if (rc == -EBADMSG) {
		/* Sample overrun.  Ignore in polled mode. */
		if (IS_ENABLED(CONFIG_LIS2DH_TRIGGER)) {
			overrun = "[OVERRUN] ";
		}
		rc = 0;
	}
	if (rc == 0) {
		rc = sensor_channel_get(sensor,
					SENSOR_CHAN_ACCEL_XYZ,
					accel);
	}
	if (rc < 0) {
		printf("ERROR: Update failed: %d\n", rc);
	} else {
		printf("#%u @ %u ms: %sx %f , y %f , z %f\n",
		    	count, k_uptime_get_32(), overrun,
		    	sensor_value_to_double(&accel[0]),
		    	sensor_value_to_double(&accel[1]),
		    	sensor_value_to_double(&accel[2]));
	}
}

#if CONFIG_LIS2DH_ODR_RUNTIME
void ODR_set(const struct device *sensor, uint16_t val1){
	const struct sensor_value ODR_value = {val1, 0}; //0, 1, 10, 25, 50, 100, 200, 400, 1620, 1344, 5376

	int status = sensor_attr_set(
		sensor,
		SENSOR_CHAN_ACCEL_XYZ,
		SENSOR_ATTR_SAMPLING_FREQUENCY,
		&ODR_value 
	);
	if(unlikely(status < 0)){
		printf("Failed to set ODR (%u) with erno: %i\n", ODR_value.val1, status);
	} else if(ODR_value.val1 == 0){
		printf("\033[1;34mSet ODR to \033[1;35m0\033[1;36m (power-down)\033[0m\n");
	} else {
		printf("\033[1;34mSet ODR to \033[1;35m%u\033[0m\n", ODR_value.val1);
	}
	
}
#endif

#if CONFIG_LIS2DH_TRIGGER
void slope_TH_set(const struct device *sensor, uint16_t val1, uint16_t val2){
	const struct sensor_value slope_TH_value = {val1, val2};
	
	int status = sensor_attr_set(sensor,
		SENSOR_CHAN_ACCEL_XYZ,
		SENSOR_ATTR_SLOPE_TH,
		&slope_TH_value
	);

	if(status < 0){
		printf("Failed to set SLOPE_TH (%u) with erno: %i", slope_TH_value.val1, status);
	}
}

void slope_DUR_set(const struct device *sensor, uint8_t val1){
	const struct sensor_value slope_DUR_value = {val1, 0};
	
	int status = sensor_attr_set(sensor,
		SENSOR_CHAN_ACCEL_XYZ,
		SENSOR_ATTR_SLOPE_DUR,
		&slope_DUR_value
	);

	if(status < 0){
		printf("Failed to set SLOPE_DUR (%u) with erno: %i", slope_DUR_value.val1, status);
	}
}

static void trigger_handler(const struct device *dev,
			    struct sensor_trigger *trig)
{
	fetch_and_display(dev);
}
#endif

void act_TH_set(const struct device *sensor, uint16_t val1, uint16_t val2){
	const struct sensor_value act_TH_value = {val1, val2};
	
	int status = sensor_attr_set(sensor,
		SENSOR_CHAN_ACCEL_XYZ,
		SENSOR_ATTR_LIS2DH_ACT_TH,
		&act_TH_value
	);

	if(status < 0){
		printf("Failed to set ACT_TH (%u) with erno: %i", act_TH_value.val1, status);
	}
}

void act_DUR_set(const struct device *sensor, uint16_t val1){
	const struct sensor_value act_DUR_value = {val1, 0};
	
	int status = sensor_attr_set(sensor,
		SENSOR_CHAN_ACCEL_XYZ,
		SENSOR_ATTR_LIS2DH_ACT_DUR,
		&act_DUR_value
	);

	if(status < 0){
		printf("Failed to set ACT_DUR (%u) with erno: %i", act_DUR_value.val1, status);
	}
}

void sample_pm_device_cb(const struct device *dev, int status, uint32_t *state, void *arg){
	printf("yeet? dev: %s, status: %i, state: %ls", dev->name, status, state);
}


void main(void)
{
	const struct device *sensor = device_get_binding(DT_LABEL(DT_INST(0, st_lis2dh)));

	if (unlikely(sensor == NULL)) {
		printf("Could not get %s device\n",
		       DT_LABEL(DT_INST(0, st_lis2dh)));
		return;
	}

	//act_TH_set(sensor, 8, 0);
	//act_DUR_set(sensor, 1);
	ODR_set(sensor, (uint16_t)10);

#if CONFIG_LIS2DH_TRIGGER
	struct sensor_trigger trig;
	int rc;

	trig.type = SENSOR_TRIG_DATA_READY;
	trig.chan = SENSOR_CHAN_ACCEL_XYZ;

	rc = sensor_trigger_set(sensor, &trig, trigger_handler);
	if (rc != 0) {
		printf("Failed to set trigger: %d\n", rc);
		return;
	}

	//slope_TH_set(sensor, 8, 0);
	//slope_DUR_set(sensor, 1);
	printf("Waiting for triggers\n");
	k_sleep(K_MSEC(3000));
	while (true) {
		/* power down the sensor */
		pm_device_state_set(sensor, PM_DEVICE_STATE_LOW_POWER, NULL, NULL);
		k_sleep(K_MSEC(1000));
		
		/* re-enable the sensor */
		pm_device_state_set(sensor, PM_DEVICE_STATE_ACTIVE, NULL, NULL);

#if	defined(CONFIG_LIS2DH_AXES_RUNTIME)
		k_sleep(K_MSEC(500));
		lis2dh_axis_set(sensor, SENSOR_CHAN_ACCEL_X, false);
		k_sleep(K_MSEC(500));
		lis2dh_axis_set(sensor, SENSOR_CHAN_ACCEL_X, true);
		lis2dh_axis_set(sensor, SENSOR_CHAN_ACCEL_Y, false);
		k_sleep(K_MSEC(500));
		lis2dh_axis_set(sensor, SENSOR_CHAN_ACCEL_Y, true);
		lis2dh_axis_set(sensor, SENSOR_CHAN_ACCEL_Z, false);
		k_sleep(K_MSEC(500));
		lis2dh_axis_set(sensor, SENSOR_CHAN_ACCEL_Z, true);
#endif
#if defined(CONFIG_LIS2DH_OPER_MODE_RUNTIME)
		k_sleep(K_MSEC(500));
		lis2dh_set_oper_mode(sensor, OPER_MODE_LOW_POWER);
		k_sleep(K_MSEC(500));
		lis2dh_set_oper_mode(sensor, OPER_MODE_HIGH_RES);
		k_sleep(K_MSEC(500));
		lis2dh_set_oper_mode(sensor, OPER_MODE_NORMAL);
#endif
		k_sleep(K_MSEC(1000));
	}
#else /* CONFIG_LIS2DH_TRIGGER */
	printf("Polling at 10 Hz\n");
	while (true) {
		fetch_and_display(sensor);
		k_sleep(K_MSEC(100));
	}
#endif /* CONFIG_LIS2DH_TRIGGER */
}
