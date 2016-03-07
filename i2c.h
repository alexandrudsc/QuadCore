/* 
 * File:   i2c.h
 * Author: Alexandru
 * Header file for i2c driver in slave configuration. The only supported operation is read.
 * Created on February 29, 2016, 5:04 PM
 */

#ifndef I2C_H
#define	I2C_H

#define SDA     
#define SCL
#define SDA_DIR     TRISC7
#define SCL_DIR     TRISC6

#define I2C_SPEED   100               // kbps

// slave address
#define I2C_ADDR    0x20

// 7 bits slave address
#define I2C_ADDR_7_bits     0x10 

#define INPUT_BUFFER_SIZE     20

void i2c_init_slave();
void i2c_init_master();
void i2c_master_start();
void i2c_write_byte();
unsigned char i2c_read_byte();


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

