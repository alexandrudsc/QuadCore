/* 
 * File:   i2c.h
 * Author: Alexandru
 * Created on February 29, 2016, 5:04 PM
 * Header file for i2c driver PIC16f917 in slave configuration. [Only read operation is available: EDIT write to master added].
 * The writing to master is done using an output buffer and the bytes are written from LEFT TO RIGHT  
 * When an i2c event occurs an interrupt is generated. In the interrupt service routine it is implemented a callback mechanism.
 * I2C communication is implemented as a finite state machine (FSM). 
 * We considered only two states for the slave configuration (only read from master)
 */

#ifndef I2C_H
#define	I2C_H

// define a null address
#define NULL 0

#define SDA_BIT     PORTD7     
#define SCL         PORTD6
#define SDA_DIR     TRISC7
#define SCL_DIR     TRISC6

#define I2C_SPEED   100               // kbps

// slave address
#define I2C_ADDR    0x20

// 7 bits slave address
#define I2C_ADDR_7_bits     0x10 

/* INPUT MESSAGE: 2 bytes PWM duty (10bits PWM), 
 *              2 bytes PWM frequency, 1 byte direction, 
 *              2 motor speed, 
 *              1 byte motor direction
 *              1 byte number of bytes used within message             
 */
#define INPUT_BUFFER_SIZE     8

/* OUTPUT MESSAGE:
 */
#define OUTPUT_BUFFER_SIZE     5

// structure of a message received for motor control
union message_in {
    unsigned char input_buff[INPUT_BUFFER_SIZE];
    unsigned char nr_bytes  ;                       // 1 byte number of bytes used within message
};
#define MOTOR_SPEED_BYTE1 input_buff[1]
#define MOTOR_SPEED_BYTE2 input_buff[2]

#define PWM_DUTY_BYTE1    input_buff[3]
#define PWM_DUTY_BYTE2    input_buff[4]

#define PWM_FREQ_BYTE1    input_buff[5]
#define PWM_FREQ_BYTE2    input_buff[6]

#define MOTOR_DIR         input_buff[7]

typedef union message_in MESSAGE_IN;

// structure of a message to be sent to the master
union message_out {
    unsigned char output_buff[OUTPUT_BUFFER_SIZE];
    unsigned char nr_bytes;                         // 1 byte number of bytes used within message
};

typedef union message_out MESSAGE_OUT;

#define DISTANCE_BYTE1 output_buff[1]
#define DISTANCE_BYTE2 output_buff[2]
#define DISTANCE_BYTE3 output_buff[3]
#define DISTANCE_BYTE4 output_buff[4]

// Callback handler for incoming i2c Message 
typedef void (handler_in)(MESSAGE_IN* msg);

// Callback handler for output i2c message, i.e. the master wants to read from slave
typedef void (handler_out)(MESSAGE_OUT* msg);

// init SSP module for i2c slave configuration
void i2c_init_slave();

// set the handler for a complete i2c input message
void i2c_set_handler_in(handler_in h);

// set the handler for a complete i2c outptu message
void i2c_set_handler_out(handler_out h);

// write one byte to master
static void i2c_write_byte();

// init SSP module for i2c slave configuration
void i2c_init_master();

// resolve a complete message
static void msg_in_resolve();

// restart input comunication
static void msg_in_restart();

// add a byte to the message
static void msg_in_add_byte(char byte);

// read one byte from master
static unsigned char i2c_read_byte();

// a master requests a message to be sent
static void msg_out_request();

// i2c interrupt handler
void i2c_interrupt();

// start writing as master
void i2c_master_start();


#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

