rtc folder has three files ( rtc.c / rtc.h / RTC.pdf(datasheet) ) and it uses the i2c folder and the files in them.

i2c folder has two files ( i2c.c / i2c.h ) and it uses the utils folder and the files in them.

utils folder has two types ( data_types.h / bit_handle.h )

make sure to put all three folders in your project and add them to your directories to avoid linking errors, also create a "main.c" file to test the drivers, don't forget to call the initialization functions.

the i2c driver can be used with other microcontroller just make sure to change the addresses according to the new microcontroller in "i2c.h"
