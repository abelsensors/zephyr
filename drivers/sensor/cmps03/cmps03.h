#ifndef ZEPHYR_DRIVERS_SENSOR_CMPS03_CMPS03_H_
#define ZEPHYR_DRIVERS_SENSOR_CMPS03_CMPS03_H_

#include <zephyr/types.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>

#define DT_DRV_COMPAT cmps03

#define CMPS03_BUS_I2C DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)

union cmps03_bus_config {

uint16_t i2c_addr;

};

typedef int (*cmps03_bus_check_fn)(const struct device *bus,
				   const union cmps03_bus_config *bus_config);
typedef int (*cmps03_reg_read_fn)(const struct device *bus,
				  const union cmps03_bus_config *bus_config,
				  uint8_t start, uint8_t *buf, int size);
typedef int (*cmps03_reg_write_fn)(const struct device *bus,
				   const union cmps03_bus_config *bus_config,
				   uint8_t reg, uint8_t val);

struct cmps03_bus_io {
	cmps03_bus_check_fn check;
	cmps03_reg_read_fn read;
	cmps03_reg_write_fn write;
};

extern const struct cmps03_bus_io cmps03_bus_io_i2c;

#define CMPS03_REG_PRESS_MSB            0xF7
#define CMPS03_REG_COMP_START           0x88
#define CMPS03_REG_HUM_COMP_PART1       0xA1
#define CMPS03_REG_HUM_COMP_PART2       0xE1
#define CMPS03_REG_ID                   0xD0
#define CMPS03_REG_CONFIG               0xF5
#define CMPS03_REG_CTRL_MEAS            0xF4
#define CMPS03_REG_CTRL_HUM             0xF2
#define CMPS03_REG_STATUS               0xF3

#define BMP280_CHIP_ID_SAMPLE_1         0x56
#define BMP280_CHIP_ID_SAMPLE_2         0x57
#define BMP280_CHIP_ID_MP               0x58

#define CMPS03_CHIP_ID                  0x60
#define CMPS03_MODE_SLEEP               0x00
#define CMPS03_MODE_FORCED              0x01
#define CMPS03_MODE_NORMAL              0x03
#define CMPS03_SPI_3W_DISABLE           0x00

#if defined CONFIG_CMPS03_MODE_NORMAL
#define CMPS03_MODE CMPS03_MODE_NORMAL
#elif defined CONFIG_CMPS03_MODE_FORCED
#define CMPS03_MODE CMPS03_MODE_FORCED
#endif

#if defined CONFIG_CMPS03_TEMP_OVER_1X
#define CMPS03_TEMP_OVER                (1 << 5)
#elif defined CONFIG_CMPS03_TEMP_OVER_2X
#define CMPS03_TEMP_OVER                (2 << 5)
#elif defined CONFIG_CMPS03_TEMP_OVER_4X
#define CMPS03_TEMP_OVER                (3 << 5)
#elif defined CONFIG_CMPS03_TEMP_OVER_8X
#define CMPS03_TEMP_OVER                (4 << 5)
#elif defined CONFIG_CMPS03_TEMP_OVER_16X
#define CMPS03_TEMP_OVER                (5 << 5)
#endif

#if defined CONFIG_CMPS03_PRESS_OVER_1X
#define CMPS03_PRESS_OVER               (1 << 2)
#elif defined CONFIG_CMPS03_PRESS_OVER_2X
#define CMPS03_PRESS_OVER               (2 << 2)
#elif defined CONFIG_CMPS03_PRESS_OVER_4X
#define CMPS03_PRESS_OVER               (3 << 2)
#elif defined CONFIG_CMPS03_PRESS_OVER_8X
#define CMPS03_PRESS_OVER               (4 << 2)
#elif defined CONFIG_CMPS03_PRESS_OVER_16X
#define CMPS03_PRESS_OVER               (5 << 2)
#endif

#if defined CONFIG_CMPS03_HUMIDITY_OVER_1X
#define CMPS03_HUMIDITY_OVER            1
#elif defined CONFIG_CMPS03_HUMIDITY_OVER_2X
#define CMPS03_HUMIDITY_OVER            2
#elif defined CONFIG_CMPS03_HUMIDITY_OVER_4X
#define CMPS03_HUMIDITY_OVER            3
#elif defined CONFIG_CMPS03_HUMIDITY_OVER_8X
#define CMPS03_HUMIDITY_OVER            4
#elif defined CONFIG_CMPS03_HUMIDITY_OVER_16X
#define CMPS03_HUMIDITY_OVER            5
#endif

#if defined CONFIG_CMPS03_STANDBY_05MS
#define CMPS03_STANDBY                  0
#elif defined CONFIG_CMPS03_STANDBY_62MS
#define CMPS03_STANDBY                  (1 << 5)
#elif defined CONFIG_CMPS03_STANDBY_125MS
#define CMPS03_STANDBY                  (2 << 5)
#elif defined CONFIG_CMPS03_STANDBY_250MS
#define CMPS03_STANDBY                  (3 << 5)
#elif defined CONFIG_CMPS03_STANDBY_500MS
#define CMPS03_STANDBY                  (4 << 5)
#elif defined CONFIG_CMPS03_STANDBY_1000MS
#define CMPS03_STANDBY                  (5 << 5)
#elif defined CONFIG_CMPS03_STANDBY_2000MS
#define CMPS03_STANDBY                  (6 << 5)
#elif defined CONFIG_CMPS03_STANDBY_4000MS
#define CMPS03_STANDBY                  (7 << 5)
#endif

#if defined CONFIG_CMPS03_FILTER_OFF
#define CMPS03_FILTER                   0
#elif defined CONFIG_CMPS03_FILTER_2
#define CMPS03_FILTER                   (1 << 2)
#elif defined CONFIG_CMPS03_FILTER_4
#define CMPS03_FILTER                   (2 << 2)
#elif defined CONFIG_CMPS03_FILTER_8
#define CMPS03_FILTER                   (3 << 2)
#elif defined CONFIG_CMPS03_FILTER_16
#define CMPS03_FILTER                   (4 << 2)
#endif

#define CMPS03_CTRL_MEAS_VAL            (CMPS03_PRESS_OVER | \
					 CMPS03_TEMP_OVER |  \
					 CMPS03_MODE)
#define CMPS03_CONFIG_VAL               (CMPS03_STANDBY | \
					 CMPS03_FILTER |  \
					 CMPS03_SPI_3W_DISABLE)


#define CMPS03_CTRL_MEAS_OFF_VAL		(CMPS03_PRESS_OVER | \
					 CMPS03_TEMP_OVER |  \
					 CMPS03_MODE_SLEEP)

#endif /* ZEPHYR_DRIVERS_SENSOR_CMPS03_CMPS03_H_ */
