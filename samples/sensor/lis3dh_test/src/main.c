/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>

int lis2dh_reset(const struct device *dev);

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
	const struct sensor_value slope_DUR_value = {(uint16_t)val1, 0};
	
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

void main(void)
{
	const struct device *sensor = device_get_binding(DT_LABEL(DT_INST(0, st_lis2dh)));

	if (unlikely(sensor == NULL)) {
		printf("Could not get %s device\n",
		       DT_LABEL(DT_INST(0, st_lis2dh)));
		return;
	}

	ODR_set(sensor, (uint16_t)50);
	//slope_TH_set(sensor, 2, 1);
	//slope_DUR_set(sensor, 2);
	

#if CONFIG_LIS2DH_TRIGGER
	{
		struct sensor_trigger trig;
		int rc;
		int status;

		trig.type = SENSOR_TRIG_DATA_READY;
		//trig.type = SENSOR_TRIG_DELTA;
		trig.chan = SENSOR_CHAN_ACCEL_XYZ;

		/*
		if (IS_ENABLED(CONFIG_LIS2DH_ODR_RUNTIME)) {
			struct sensor_value odr = {
				.val1 = 1,
			};

			rc = sensor_attr_set(sensor, trig.chan,
					     SENSOR_ATTR_SAMPLING_FREQUENCY,
					     &odr);
			if (rc != 0) {
				printf("Failed to set odr: %d\n", rc);
				return;
			}
			printf("Sampling at %u Hz\n", odr.val1);
		}
		*/

		rc = sensor_trigger_set(sensor, &trig, trigger_handler);
		if (rc != 0) {
			printf("Failed to set trigger: %d\n", rc);
			return;
		}

		printf("Waiting for triggers\n");

		while (true) {
			ODR_set(sensor, (uint16_t)50);						//set ODR to 50
			k_sleep(K_MSEC(1500));
			ODR_set(sensor, (uint16_t)0);						//set ODR to 0 (power-down)
			k_sleep(K_MSEC(1500));
			ODR_set(sensor, (uint16_t)50);						//set ODR to 50
			k_sleep(K_MSEC(1500));

			status = lis2dh_reset(sensor);						//reset all lis3dh registers to defaults
			if (unlikely(status < 0)) {
				printf("Failed to reset sensor: %d\n", status);
				return;
			}

			rc = sensor_trigger_set(sensor, &trig, trigger_handler);	//configure data ready interrupt
			if (unlikely(rc < 0)) {
				printf("Failed to set trigger: %d\n", rc);
				return;
			}
			k_sleep(K_MSEC(100));
		}
	}
#else /* CONFIG_LIS2DH_TRIGGER */
	printf("Polling at 10 Hz\n");
	while (true) {
		fetch_and_display(sensor);
		k_sleep(K_MSEC(100));
	}
#endif /* CONFIG_LIS2DH_TRIGGER */
}
