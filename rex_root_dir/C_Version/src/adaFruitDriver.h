/*
 * adaFruitDriver.h
 *
 *  Created on: Nov 1, 2013
 *      Author: kartik
 */

#ifndef ADAFRUITDRIVER_H_
#define ADAFRUITDRIVER_H_

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <stdint.h>

#include "slaveDevice.h"


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

//int i;						// counter for loops
int I2CBus;

int8_t readI2CByte(int8_t, int8_t);
void writeI2CByte(int8_t, int8_t, int8_t);
void servoControllerReset(int8_t);

void initializeServoDriver(int, int8_t);
void setPWMValue(int, int8_t, int8_t, int16_t);


#endif /* ADAFRUITDRIVER_H_ */
