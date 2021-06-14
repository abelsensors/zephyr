
#include <zephyr.h>
#include <net/socket.h>
#include <ztest.h>
#include <device.h>
#include <sys/fdtable.h>
#include "lis2dh.h"


static int lis2dh_i2c_read_data_mock(const struct device *dev, uint8_t reg_addr,
				 uint8_t *value, uint8_t len)
{
	// struct lis2dh_data *data = dev->data;
	// const struct lis2dh_config *cfg = dev->config;

	// return i2c_burst_read(data->bus, cfg->bus_cfg.i2c_slv_addr,
	// 		      reg_addr | LIS2DH_AUTOINCREMENT_ADDR,
	// 		      value, len);

    return 0;
}

static int lis2dh_i2c_write_data_mock(const struct device *dev, uint8_t reg_addr,
				  uint8_t *value, uint8_t len)
{
	// struct lis2dh_data *data = dev->data;
	// const struct lis2dh_config *cfg = dev->config;

	// return i2c_burst_write(data->bus, cfg->bus_cfg.i2c_slv_addr,
	// 		       reg_addr | LIS2DH_AUTOINCREMENT_ADDR,
	// 		       value, len);

    return 0;
}

static int lis2dh_i2c_read_reg_mock(const struct device *dev, uint8_t reg_addr,
				uint8_t *value)
{
	// struct lis2dh_data *data = dev->data;
	// const struct lis2dh_config *cfg = dev->config;

	// return i2c_reg_read_byte(data->bus,
	// 			 cfg->bus_cfg.i2c_slv_addr,
	// 			 reg_addr, value);
    return 0;
}

static int lis2dh_i2c_write_reg_mock(const struct device *dev, uint8_t reg_addr,
				uint8_t value)
{
	// struct lis2dh_data *data = dev->data;
	// const struct lis2dh_config *cfg = dev->config;

	// return i2c_reg_write_byte(data->bus,
	// 			  cfg->bus_cfg.i2c_slv_addr,
	// 			  reg_addr, value);
    return 0;
}

static int lis2dh_i2c_update_reg_mock(const struct device *dev, uint8_t reg_addr,
				  uint8_t mask, uint8_t value)
{
// 	struct lis2dh_data *data = dev->data;
// 	const struct lis2dh_config *cfg = dev->config;

// 	return i2c_reg_update_byte(data->bus,
// 				   cfg->bus_cfg.i2c_slv_addr,
// 				   reg_addr, mask, value);
//
return 0; 
}

static const struct lis2dh_transfer_function lis2dh_i2c_transfer_fn = {
	.read_data = lis2dh_i2c_read_data_mock,
	.write_data = lis2dh_i2c_write_data_mock,
	.read_reg  = lis2dh_i2c_read_reg_mock,
	.write_reg  = lis2dh_i2c_write_reg_mock,
	.update_reg = lis2dh_i2c_update_reg_mock,
};

int lis2dh_i2c_init(const struct device *dev)
{
	struct lis2dh_data *data = dev->data;

	data->hw_tf = &lis2dh_i2c_transfer_fn;

	return 0;
}