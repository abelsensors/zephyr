/*
 * Copyright (c) 2021 Abel Sensors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>
#include <drivers/gpio.h>

#define GPIO_EXPANDER DT_LABEL(DT_NODELABEL(gpio_expander))
#define I2C           DT_LABEL(DT_NODELABEL(i2c1))

static const struct device *gpio_dev;
static const struct device *i2c_dev;

void main(void)
{
	gpio_dev = device_get_binding(GPIO_EXPANDER);
	i2c_dev  = device_get_binding(I2C);

	if (gpio_dev == NULL || i2c_dev == NULL) {
		while (1) {
			printk("!");
			k_msleep(50);
		}
	}

	gpio_config(gpio_dev, 0, GPIO_INPUT | GPIO_PULL_UP);
	gpio_config(gpio_dev, 1, GPIO_INPUT | GPIO_PULL_UP);

	gpio_config(gpio_dev, 2, GPIO_INPUT | GPIO_PULL_DOWN);
	gpio_config(gpio_dev, 3, GPIO_INPUT | GPIO_PULL_DOWN);

	for (int i = 4; i <= 7; i++) {
		gpio_config(gpio_dev, i, GPIO_OUTPUT | GPIO_PULL_DOWN);
	}

	uint8_t value = 0xFF;
	int result = 0xFF;

	while (1) {
		k_msleep(500);
		gpio_port_set_masked_raw(gpio_dev, 0xF0, value);
		gpio_port_get_raw(gpio_dev, &result);
		printk("result: %d\n", result & 0x0F);
		value ^= 0xFF;
	}
}
