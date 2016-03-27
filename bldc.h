/* 
 * File:   bldc.h
 * Author: Alexandru
 *
 * Created on 14 martie 2016, 18:39
 */

#ifndef BLDC_H
#define	BLDC_H

#include <xc.h>
#include "uc_config.h"

#define A_HIGH RD0
#define A_LOW RD1

#define B_HIGH RD4
#define B_LOW RD5

#define C_HIGH RD6
#define C_LOW RD7

#define FORWARD 1
#define BACKWARDS -1

#define SPEED_CHANGING 1
#define SPEED_NOT_CHANGING 0

void motor_go_forward();
void motor_go_back();

void motor_break();

void set_motor_speed(int speed);
void motor_dir(char dir);
void motor_go(int speed);

// speed in rpms
static void accelerate_to (int speed);
static void deccelerate_to (int speed);

static void delay_milis(int milis);
static void delay_micros(int micros);

// logic pins control
static void all_low();
static void phase_A();
static void phase_B();
static void phase_C();



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BLDC_H */

