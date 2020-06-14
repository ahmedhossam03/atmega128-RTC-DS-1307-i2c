#ifndef I2C_H_
#define I2C_H_

#include "../utils/data_types.h"
#include "../utils/bit_handle.h"

#define I2C_BITRATE_R			(*(volatile uint8*) 0x70)
#define I2C_CTRL_R			(*(volatile uint8*) 0x74)
#define I2C_STAT_R			(*(volatile uint8*) 0x71)
#define I2C_DATA_R			(*(volatile uint8*) 0x73)
#define I2C_ADD_R			(*(volatile uint8*) 0x72)

/* control status */
#define I2C_START_COM			0x08
#define I2C_RESTART_COM			0x10

/* master transmit status */
#define I2C_MT_ADD_BYTE_ACK		0x18
#define I2C_MT_ADD_BYTE_NACK		0x20
#define I2C_MT_DATA_BYTE_ACK		0x28
#define I2C_MT_DATA_BYTE_NACK		0x30

/* master receive status */
#define I2C_MR_ADD_BYTE_ACK		0x40
#define I2C_MR_ADD_BYTE_NACK		0x48
#define I2C_MR_DATA_BYTE_ACK		0x50
#define I2C_MR_DATA_BYTE_NACK		0x58

void i2c_init();
Bool i2c_start();
Bool i2c_restart();
void i2c_stop();
void i2c_wait();

Bool i2c_write_byte(uint8, uint8);
Bool i2c_read_byte(uint8*, uint8);

#endif /* I2C_H_ */