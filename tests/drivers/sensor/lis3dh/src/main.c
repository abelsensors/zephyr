/*
 * Copyright (c) 2021 Abel Sensor
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <net/socket.h>
#include <ztest.h>
#include <device.h>
#include <sys/fdtable.h>

void test_basic()
{
	zassert_true(true, "");
	const struct device *sensor = 
	device_get_binding(DT_LABEL(DT_INST(0, st_lis2dh)));
	zassert_not_null(sensor, "sensor binding not working");

}

void test_main(void)
{
	ztest_test_suite(lis3dh_test, 
	ztest_unit_test(test_basic)
	);
	ztest_run_test_suite(lis3dh_test);
}
