/*
 * 
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ublox_neom8

/** @file
 * @brief Atmel SAM MCU family Quadrature Decoder (QDEC/TC) driver.
 */

#include <errno.h>
#include <sys/__assert.h>
#include <sys/util.h>
#include <device.h>
#include <init.h>
#include <drivers/sensor.h>

#include <logging/log.h>


/* Device constant configuration parameters */
struct ublox_m8_dev_cfg {
	uint8_t i2c_slave_addr;
	const struct device *i2c_master;	
};

/* Device run time data */
struct ublox_m8_dev_data {
	uint16_t position;
};

#define DEV_NAME(dev) ((dev)->name)

static int ublox_m8_fetch(const struct device *dev, enum sensor_channel chan)
{
	printk("\nfetching m8 stuff");

	return 0;
}

static int ublox_m8_get(const struct device *dev, enum sensor_channel chan,
			struct sensor_value *val)
{
	printk("\ngetting m8 things");
	return 0;
}

static int ublox_m8_initialize(const struct device *dev)
{
	__ASSERT_NO_MSG(dev != NULL);

	struct ublox_m8_dev_cfg *const config = (struct ublox_m8_dev_cfg *)dev->config;
	struct ublox_m8_dev_data *data = dev->data;

	if (config->i2c_slave_addr == 0) {
		printk("No I2C slave adres in neo-m8 init!\n");
		return EINVAL;
	}

	if (config->i2c_master == NULL) {
		printk("No I2C master in neo-m8 init!\n");
		return EINVAL;
	}

	volatile int a = config->i2c_slave_addr;
	volatile int b = config->i2c_master;

printk("\n");
	// /* Connect pins to the peripheral */
	// soc_gpio_list_configure(dev_cfg->pin_list, dev_cfg->pin_list_size);


	return 0;
}

static const struct sensor_driver_api ublox_m8_driver_api = {
	// sensor_attr_set_t attr_set;
	// sensor_attr_get_t attr_get;
	// sensor_trigger_set_t trigger_set;
	// sensor_sample_fetch_t sample_fetch;
	// sensor_channel_get_t channel_get;
	.sample_fetch = ublox_m8_fetch,
	.channel_get = ublox_m8_get,
};

static const struct ublox_m8_dev_cfg m8inst_sam_config = {	
	.i2c_slave_addr = DT_INST_REG_ADDR(0),                               
	.i2c_master = DEVICE_DT_GET(DT_INST_BUS(0))                          
	};								
							
	static struct ublox_m8_dev_data m8inst_sam_data;		
		


DEVICE_DT_INST_DEFINE(0, ublox_m8_initialize, NULL,		\
			    &m8inst_sam_data, &m8inst_sam_config, \
			    POST_KERNEL, 80,	\
			    &ublox_m8_driver_api);
