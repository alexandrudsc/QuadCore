/*
 * File:   i2c.c
 * Author: Alexandru
 * Created on November 10, 2015, 2:18 PM
 * Driver for i2c slave configuration. [Only read operation is available].
 * The writing to master is done using an output buffer and the bytes are written from LEFT TO RIGHT.  
 * When an i2c event occurs, an interrupt is generated.
 * A complete input message is defined in "i2c.h"
 */

#include <pic16f917.h>

#include "i2c.h"
#include "uc_config.h"

//  A complete input message is defined in "i2c.h"
MESSAGE_IN msg_in;

//  A complete output message is defined in "i2c.h"
MESSAGE_OUT msg_out;

// pointer to handler function incoming messages
handler_in* p_in = NULL;

// pointer to handler function out messages
handler_out* p_out = NULL;

// init SSP module i2c slave config
void i2c_init_slave() {
    
    (*p_out)();
    (*p_in)(msg_in);
    
    // SCL and SDA pins configured as inputs
    SDA_DIR = 1;
    SCL_DIR = 1;

    // SSP address. set i2c address; the LSb must be 0: it will be used as R/W flag 
    SSPADD = I2C_ADDR_7_bits << 1;

    // select and enable i2c slave mode 7 bit addressing
    SSPCON = 0x36;

    // enable SSP interrupts for each i2c event  
    GIE = 1; // global software interrupts
    PEIE = 1; // global pheripherals interrupts
    SSPIE = 1; // SSP interrupt
}

// init SSP module i2c master config
void i2c_init_master() {
    // to be implemented if master configuration required
}

// begin i2c transmission as master
void i2c_master_start() {
    // to be implemented if master configuration required
}

// read byte from input register
static unsigned char i2c_read_byte() {
    return SSPBUF; // return the value of the register
}

// write one byte to master
static void i2c_write_byte() {
    
    // write a byte from the output message to the buffer register if possibile
    if (msg_out.nr_bytes > 0){
        SSPBUF = msg_out.output_buff [msg_out.nr_bytes - 1];
        
        // delete one byte from message
        msg_out.nr_bytes --;
    }
}

// public function to set a handler for a complete input message
void i2c_set_handler_in(handler_in* h) {
    p_in = h;
}

// public function to set a handler for a resolving a request output message
void i2c_set_handler_out(handler_out* h) {
    p_out = h;
}

/* handler for all interrupts. We use it only for I2C events
 * I2C communication is implemented as a finite state machine (FSM). 
 * We considered only two states for the slave configuration (only read from master)
 */
interrupt void ISR_Handler() {

    // SSP interrupt (i2c) occured
    if (SSPIF) {

        /* State 1: 
         * start condition occurred last &&
         * master writes to slave &&
         * last byte was an address &&
         * buffer is fuull
         */
        if (SSPSTATbits.S && SSPSTATbits.READ_WRITE == 0 && SSPSTATbits.DATA_ADDRESS == 0 && BF == 1) {
            // a new message is started
            msg_in_restart();
            // add to the message the byte we just read 
            //msg_in_add_byte(i2c_read_byte());
        }
        /* State 2:
         * start condition occurred last &&
         * master writes to slave &&
         * last byte was a data
         */
        else if (SSPSTATbits.S && SSPSTATbits.READ_WRITE == 0 && SSPSTATbits.DATA_ADDRESS) {

            // add the byte we just read, to the input buffer
            msg_in_add_byte(i2c_read_byte());

            // when we have read a complete message. call the handler
            if (msg_in.nr_bytes == INPUT_BUFFER_SIZE)
                msg_in_resolve();

            // in case of new message reset communication
            if (msg_in.nr_bytes > INPUT_BUFFER_SIZE)
                msg_in_restart();
        }
        /* State3:
         * start condition occurred last &&
         * master reads from slave &&
         * last byte was an address
         */
        else if (SSPSTATbits.S && SSPSTATbits.READ_WRITE == 1 && SSPSTATbits.DATA_ADDRESS == 0) {
            msg_out_request();
        }
        
        /* State3:
         * start condition occurred last &&
         * master reads from slave &&
         * last byte was data &&
         * buffer is empty
         */
        else if (SSPSTATbits.S && SSPSTATbits.READ_WRITE == 1 && SSPSTATbits.DATA_ADDRESS && BF == 0){
            i2c_write_byte();
        }
        
        
        SSPIF = 0; // Clear the interrupt flag.

    }
}

static void msg_in_add_byte(char byte) {
    msg_in.nr_bytes ++;
    msg_in.input_buff[msg_in.nr_bytes - 1] = byte;
}

static void msg_in_resolve() {
    if (p_in != NULL)
        (*p_in)(msg_in);
}

static void msg_in_restart() {
    msg_in.nr_bytes = 0;
}

static void msg_out_request() {
    if (p_out != NULL)
        msg_out = (*p_out)();
}