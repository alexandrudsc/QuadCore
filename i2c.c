/*
 * File:   i2c.c
 * Author: Alexandru
 * Created on November 10, 2015, 2:18 PM
 * Driver for i2c slave configuration. [Only read operation is available: EDIT write to master added].
 * The writing to master is done using an output buffer and the bytes are written from LEFT TO RIGHT.  
 * When an i2c event occurs, an interrupt is generated.
 * A complete input message is defined in "i2c.h"
 */

#include <pic16f917.h>
#include <pic.h>

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
    
    PORTD = 0x00;
    
    // SCL and SDA pins configured as inputs
    SDA_DIR = 1;
    SCL_DIR = 1;

    // SSP address. set i2c address; the LSb must be 0: it will be used as R/W flag 
    SSPADD = I2C_ADDR_7_bits << 1;

    // select and enable i2c slave mode 7 bit addressing
    SSPCON = 0x36;
    
    // clear any previous i2c event
    SSPSTAT = 0x00;
    SSPOV = 0;
    BF = 0;
    
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
    // write a byte from the output message to the buffer register if possible
    if (msg_out.nr_bytes > 0){
        
        // rewrite until collision is avoided
        do
        {
            WCOL = 0;                           // delete write collision flag
            SSPBUF = msg_out.output_buff [msg_out.nr_bytes - 1];
        }while (WCOL);                          
        
        // delete one byte from message
        msg_out.nr_bytes --;
        
        CKP = 1;            // release SCL line
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

/*
 * I2C communication is implemented as a finite state machine (FSM). 
 * We considered only two states for the slave configuration (only read from master)
 */
 void i2c_interrupt() {

    // SSP interrupt (i2c) occured
    if (SSPIF) { 
        
        /* State 1: Master writes to slave:
         * start condition occurred last &&
         * master writes to slave &&
         * last byte was an address &&
         * buffer is fuull
         */
        if (SSPSTATbits.S == 1 && SSPSTATbits.R_nW == 0 && SSPSTATbits.D_nA == 0 && SSPSTATbits.BF == 1) {
            CLRWDT();
            // a new message is started
            msg_in_restart();
     
            // read input register to clear address and avoid overflow
            i2c_read_byte();
            if (SSPOV == 1){
                SSPOV = 0;
                SSPIF = 0; // Clear the interrupt flag
            }
        }
        /* State 2: Master writes to slave:
         * start condition occurred last &&
         * master writes to slave &&
         * last byte was a data &&
         * buffer is full
         */
        else if (SSPSTATbits.S == 1 && SSPSTATbits.R_nW == 0 && SSPSTATbits.D_nA == 1  && SSPSTATbits.BF == 1) {
            CLRWDT();
            
            // add the byte we just read, to the input buffer
            msg_in_add_byte(i2c_read_byte());

            // when we have read a complete message. call the handler
            if (msg_in.nr_bytes == INPUT_BUFFER_SIZE)
                msg_in_resolve();

            // in case of new message reset communication
            if (msg_in.nr_bytes > INPUT_BUFFER_SIZE )
                msg_in_restart();

            if (SSPOV == 1){
                SSPOV = 0;
                SSPIF = 0; // Clear the interrupt flag
            }
        }
        /* State 3: Master reads from slave:
         * start condition occurred last &&
         * master reads from slave &&
         * last byte was an address
         */
        else if (SSPSTATbits.S == 1 && SSPSTATbits.R_nW == 1 && SSPSTATbits.D_nA == 0) {
            // request a message to be sent to master
            msg_out_request();  
            PORTD = 0x00;            
            i2c_write_byte();
            SSPIF = 0; // Clear the interrupt flag

        }
        
        /* State 4: Master reads from slave:
         * start condition occurred last &&
         * master reads from slave &&
         * last byte was data &&
         * buffer is empty
         */
        else if (SSPSTATbits.S == 1 && SSPSTATbits.R_nW == 1 && SSPSTATbits.D_nA == 1 && SSPSTATbits.BF == 0){
            i2c_write_byte();
            SSPIF = 0; // Clear the interrupt flag

        }
        /* State 5: Master NACK's the byte. It no longer reads from slave. Reset I2C logic:
         * start condition occurred last &&
         * last byte was data &&
         * buffer is empty &&
         * clock is released
         */
        else if (SSPSTATbits.S == 1 && SSPSTATbits.R_nW == 1 && SSPSTATbits.BF == 0 && CKE == 1){
            // reset slave logic
            i2c_init_slave();
        }
    }
  }

/* At this moment, the number of bytes in input messages = 1 
 * ( we keep the number of byte within the message)
 */
static void msg_in_add_byte(char byte) {
    msg_in.nr_bytes ++;
    msg_in.input_buff[msg_in.nr_bytes - 1] = byte;
}

static void msg_in_resolve() {
    if (p_in != NULL)
        (*p_in)(&msg_in);
}

static void msg_in_restart() {
    msg_in.nr_bytes = 1;                        // only the number of bytes is available now. the rest of the message must be read
}

static void msg_out_request() {
    if (p_out != NULL)
        (*p_out)(&msg_out);
}