#include "i2c.h"

void i2c_init()
{
	//initialize the  i2c with 100khz frequency
	I2C_BITRATE_R = 32;
	//enable interrupt
	//setBit(I2C_CTRL_R, 0);
}

Bool i2c_start()
{
	//clear interrupt flag to start operation, it's cleared by writing one
	setBit(I2C_CTRL_R, 7);
	//set twi start bit, to assume master and control line
	setBit(I2C_CTRL_R, 5);
	//set twi enable bit
	setBit(I2C_CTRL_R, 2);
	i2c_wait();
	//check if operation has completed well
	return ( (I2C_STAT_R & 0xF8) == I2C_START_COM );
}

Bool i2c_restart()
{
	I2C_CTRL_R = (1 << 7) | (1 << 5) | (1 << 2);
	i2c_wait();
	return ( (I2C_STAT_R&0xF8) == I2C_RESTART_COM );
}

void i2c_stop()
{
	//clear interrupt flag to start operation, it's cleared by writing one
	setBit(I2C_CTRL_R, 7);
	//set stop bit in control register
	setBit(I2C_CTRL_R, 4);
	//set twi enable bit
	setBit(I2C_CTRL_R, 2);
}

void i2c_wait()
{
	//wait for flag to lower
	while( ( readBit(I2C_CTRL_R, 7) ) == 0 );
}

Bool i2c_write_byte(uint8 data_byte, uint8 status_code)
{
	I2C_DATA_R = data_byte;
	I2C_CTRL_R = (1 << 7) | (1 << 2);
	i2c_wait();
	return ( (I2C_STAT_R & 0xF8) == status_code );
}

Bool i2c_read_byte(uint8 *ptr_data, uint8 status_code)
{
	Bool op_status = FALSE;
	I2C_CTRL_R = (1<<7) | (1<<2);
	//check if he wanted ack
	if(status_code == I2C_MR_DATA_BYTE_ACK)
	{
		//enable ack bit in ctrl regs
		setBit(I2C_CTRL_R, 6);
	}
	i2c_wait();
	//check if operation success
	if( (I2C_STAT_R & 0xF8) == status_code )
	{
		//put data in pointer
		*ptr_data = I2C_DATA_R;
		//make operation code true
		op_status = TRUE;
	}
	//return operation status
	return op_status;
}