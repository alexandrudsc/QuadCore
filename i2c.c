/*
 * File:   i2c.c
 * Author: Alexandru
 * Driver for i2c slave configuration. Only read operation is available.
 * After one byte is read, an interrupt is generated
 * Created on November 10, 2015, 2:18 PM
 */

#include <pic16f917.h>

#include "i2c.h"
#include "uc_config.h"

char input_buff[INPUT_BUFFER_SIZE];

// init SSP module i2c slave config
void i2c_init_slave()
{
    // SCL and SDA pins configured as inputs
    SDA_DIR = 1;        
    SCL_DIR = 1;  
    
    // SSP address. set i2c address; the LSb must be 0: it will be used as R/W flag 
    SSPADD = I2C_ADDR_7_bits << 1;
    
    // select and enable i2c slave mode 7 bit addressing
    SSPCON = 0x36;
    
    // enable SSP interrupts for each i2c event  
    GIE = 1;            // global software interrupts
    PEIE = 1;           // global pheripherals interrupts
    SSPIE = 1;          // SSP interrupt
    
}

// init SSP module i2c master config
void i2c_init_master()
{
    // to be implemented if master configuration required
}

// begin i2c transmission as master
void i2c_master_start()
{
    // to be implemented if master configuration required
}

void i2c_write_byte()
{
    // to be implemented if master configuration required
}

unsigned char i2c_read_byte()
{
    if (!SSPIF){              // wait until the interrupt is generated (the falling edge of the 9th bit)
        SSPIF = 0;              // clear the interrupt flag
    }
    return SSPBUF;              // return the value of the register
}

