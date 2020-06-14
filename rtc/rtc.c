#include "rtc.h"
#include "../internal_eeprom/eeprom.h"

void rtc_init()
{
	/* initialize i2c */
	i2c_init();
}

void rtc_edit(uint8 addr, uint8 data)
{
	//start i2c
	i2c_start();
	//send write address
	i2c_write_byte(RTC_SLA_W, I2C_MT_ADD_BYTE_ACK);
	//send word
	i2c_write_byte(addr, I2C_MR_DATA_BYTE_ACK);
	//send data
	i2c_write_byte(data, I2C_MR_DATA_BYTE_ACK);
	//stop ic
	i2c_stop();
}

void rtc_set_time()
{
	//set day
	rtc_edit(0x04, 0x10);
	//set mons
	rtc_edit(0x05, 0x06);
	//set mins
	rtc_edit(0x01, 0x01);
	//set hrs
	rtc_edit(0x02, 0x01);
}

void rtc_update(RTC_STRUCT* ptr2RTC)
{
	uint8 i = 0;
	uint8 data = 0;
	uint8 regs[7] = {0};
	/* send start in i2c */
	i2c_start();
	/* reading all register from rtc according to data sheet */
	i2c_write_byte(RTC_SLA_W, I2C_MT_ADD_BYTE_ACK);
	i2c_write_byte(0x00, I2C_MT_DATA_BYTE_ACK);
	i2c_restart();
	i2c_write_byte(RTC_SLA_R, I2C_MR_DATA_BYTE_ACK);
	for(i = 0; i < 6; i++)
	{
		i2c_read_byte(&data, I2C_MR_DATA_BYTE_ACK);
		regs[i] = data;
	}
	i2c_read_byte(&data, I2C_MR_DATA_BYTE_NACK);
	regs[6] = data;
	/* stop i2c */
	i2c_stop();
	/* convert to normal seconds */
	ptr2RTC->rtc_regs[0] = regs[0] & 0x0F;
	ptr2RTC->rtc_regs[0] += ( ( regs[0] & 0x70 ) >> 4 ) * 10;
	eeprom_write(sec_add_uint, ptr2RTC->rtc_regs[0]);
	ptr2RTC->rtc_time[7] = (regs[0] & 0x0F) + '0';
	ptr2RTC->rtc_time[6] = ( ( ( regs[0] & 0x70 ) >> 4 ) ) + '0';
	ptr2RTC->rtc_time[5] = ':';
	/* convert to normal minutes */
	ptr2RTC->rtc_regs[1] = regs[1] & 0x0F;
	ptr2RTC->rtc_regs[1] += ( ( regs[1] & 0x70 ) >> 4 ) * 10;
	eeprom_write(min_add_uint, ptr2RTC->rtc_regs[1]);
	ptr2RTC->rtc_time[4] = (regs[1] & 0x0F) + '0';
	ptr2RTC->rtc_time[3] = ( ( ( regs[1] & 0x70 ) >> 4 ) ) + '0';
	ptr2RTC->rtc_time[2] = ':';
	/* convert to normal hours */
	ptr2RTC->rtc_regs[2] = regs[2] & 0x0F;
	ptr2RTC->rtc_regs[2] += ( ( regs[2] & 0x30 ) >> 4 ) * 10;
	eeprom_write(hrs_add_uint, ptr2RTC->rtc_regs[2]);
	ptr2RTC->rtc_time[1] = (regs[2] & 0x0F) + '0';
	ptr2RTC->rtc_time[0] = ( ( ( regs[2] & 0x30 ) >> 4 ) ) + '0';
	/* convert to normal days */
	ptr2RTC->rtc_regs[4] = regs[4] & 0x0F;
	ptr2RTC->rtc_regs[4] += ( ( regs[4] & 0x30 ) >> 4 ) * 10;
	eeprom_write(day_add_uint, ptr2RTC->rtc_regs[4]);
	ptr2RTC->rtc_date[1] = (regs[4] & 0x0F) + '0';
	ptr2RTC->rtc_date[0] = ( ( ( regs[4] & 0x30 ) >> 4 ) ) + '0';
	ptr2RTC->rtc_date[2] = '/';
	/* convert to normal months */
	ptr2RTC->rtc_regs[5] = regs[5] & 0x0F;
	ptr2RTC->rtc_regs[5] += ( ( regs[5] & 0x10 ) >> 4 ) * 10;
	eeprom_write(mon_add_uint, ptr2RTC->rtc_regs[5]);
	ptr2RTC->rtc_date[4] = (regs[5] & 0x0F) + '0';
	ptr2RTC->rtc_date[3] = ( ( ( regs[5] & 0x10 ) >> 4 ) ) + '0';
	ptr2RTC->rtc_date[5] = '/';
	/* convert to normal years */
	ptr2RTC->rtc_regs[6] = regs[6] & 0x0F;
	ptr2RTC->rtc_regs[6] += ( ( regs[6] & 0xF0 ) >> 4 ) * 10;
	eeprom_write(yrs_add_uint, ptr2RTC->rtc_regs[6]);
	ptr2RTC->rtc_date[7] = (regs[6] & 0x0F) + '0';
	ptr2RTC->rtc_date[6] = ( ( ( regs[6] & 0xF0 ) >> 4 ) ) + '0';
	
	for(i = 0; i < 5; i++)
	{
		eeprom_write(i+time_add, ptr2RTC->rtc_time[i]);
	}
	
	for(i = 0; i < 5; i++)
	{
		eeprom_write(i+date_add, ptr2RTC->rtc_date[i]);
	}
}
