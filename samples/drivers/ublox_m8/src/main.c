#include <errno.h>
#include <zephyr.h>
#include <device.h>
#include <drivers/i2c.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define I2C_M8N_ADDR 0x42
#define I2C_M8N_REG_ADDR 0x00
#define SUCCESS 0

const struct device * i2c_dev;

static int m8n_i2c_read_reg(const struct device *dev, uint8_t reg_addr,
                uint8_t *value)
{
    // struct m8n_data *data = dev->data;
    // const struct m8n_config *cfg = dev->config;

	int data = 0xFF;

    return i2c_reg_read_byte(i2c_dev,I2C_M8N_ADDR,I2C_M8N_REG_ADDR , data);
	// 	return i2c_transfer(i2c_dev, &msgs[0], 1, I2C_M8N_ADDR);
}

static int m8n_i2c_write_reg(const struct device *dev, uint8_t reg_addr,
                uint8_t value)
{
    // struct m8n_data *data = dev->data;
    // const struct m8n_config *cfg = dev->config;
	int data = 0xFF;

    return i2c_reg_write_byte(i2c_dev,I2C_M8N_ADDR,I2C_M8N_REG_ADDR , data);
}

//static uint16_t ubloxGetStreamBacklog( void )
//{
    // uint8_t rawdata[2] = { 0 };
    // if ( I2cReadBuffer( i2c_dev, I2C_M8N_ADDR  << 1, 0xFD, (uint8_t*) &data, 2 ) != SUCCESS ) return 0;

    // return rawdata[0] << 8 | ( rawdata[1] & 0xff );
//}

//uint8_t ubloxRunParser()
//{
    // uint8_t data[25] = { 0 };

    // uint16_t dataAvailable = ubloxGetStreamBacklog();
    // if ( dataAvailable > sizeof ( data ) )
    // {
    //     dataAvailable = sizeof ( data );
    // }

    // if ( dataAvailable && I2cReadBuffer( i2c_dev, I2C_M8N_ADDR << 1, 0xFF, data, dataAvailable ) == SUCCESS )
    // {
    //     for ( uint8_t i = 0; i < dataAvailable; i++ )
    //     {
    //         if ( IsFifoFull( &UbloxFifo ) )
    //         {
    //             abelDebugMessage( llerror, "[tracker] U-blox FIFO buffer is full!" );
    //             break;
    //         }
    //         FifoPush( &UbloxFifo, data[i] );

    //     }
    // }

    // while ( !IsFifoEmpty( &UbloxFifo ) )
    // {
    //     uint8_t retVal = ubloxInput( ublox, FifoPop( &UbloxFifo ) );
    //     if ( retVal > 0 ) return retVal;
    // }

    // return 0;
//}



void main(void)
{
	uint8_t data[16];
	int ret;

	i2c_dev = device_get_binding("I2C_1");
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
	} 
	else {
		i2c_configure(i2c_dev, I2C_SPEED_SET(I2C_SPEED_FAST));
		printk("Device binding succesful.\n");
    }

        /* Do one-byte read/write */
        data[0] = 0xFF;
        ret = m8n_i2c_write_reg(i2c_dev, 0x00, &data[0]);
        if (ret) {
            printk("Error writing to specified register: error code (%d)\n", ret);

        } else {
            printk("Wrote 0xFF to address 0x00 (%d).\n", ret);
        }

        data[0] = 0x00;
        ret = m8n_i2c_read_reg(i2c_dev, 0x00, &data[0]);
        if (ret) {
            printk("Error reading from specified register: error code (%d)\n", ret);

        } else {
            printk("Read 0x%X from address 0x00.\n", data[0]);
        }
}

// static int write_bytes(const struct device *i2c_dev, uint16_t addr, 
// 		       uint8_t *data, uint32_t num_bytes)
// {
// 	//uint8_t wr_addr[2];
// 	struct i2c_msg msgs[1];
// 	uint8_t dst;

// 	/* FRAM address */
// 	// wr_addr[0] = (addr >> 8) & 0xFF;
// 	// wr_addr[1] = addr & 0xFF;

// 	/* Setup I2C messages */

// 	/* Send the address to write to */
// 	msgs[0].buf = &dst;
// 	msgs[0].len = 0;
// 	//msgs[0].flags = I2C_MSG_WRITE;

// 	/* Data to be written, and STOP after this. */
// 	//msgs[1].buf = data;
// 	//msgs[1].len = num_bytes;
// 	msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

// 	return i2c_transfer(i2c_dev, &msgs[0], 1, I2C_M8N_ADDR);
// }

// static int read_bytes(const struct device *i2c_dev, uint16_t addr,
// 		      uint8_t *data, uint32_t num_bytes)
// {
// 	uint8_t wr_addr[2];
// 	struct i2c_msg msgs[2];

// 	/* Now try to read back from FRAM */

// 	/* FRAM address */
// 	wr_addr[0] = (addr >> 8) & 0xFF;
// 	wr_addr[1] = addr & 0xFF;

// 	/* Setup I2C messages */

// 	/* Send the address to read from */
// 	msgs[0].buf = wr_addr;
// 	msgs[0].len = 2U;
// 	msgs[0].flags = I2C_MSG_WRITE;

// 	/* Read from device. STOP after this. */
// 	msgs[1].buf = data;
// 	msgs[1].len = num_bytes;
// 	msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;

// 	return i2c_transfer(i2c_dev, &msgs[0], 2, I2C_M8N_ADDR);
// }
