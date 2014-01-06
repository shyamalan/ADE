/*
 * AdaFruitServoDriver.h
 *
 *  Created on: Aug 16, 2013
 *      Author: kartik
 */

#ifndef ADAFRUITSERVODRIVER_H_
#define ADAFRUITSERVODRIVER_H_


#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

#include "SlaveDevice.h"

#define MAX_BUS 64

//Servo constants
#define SERVOMIN 157
#define SERVOMAX 627

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

class AdaFruitServoDriver{

private:
	int8_t I2CAddress;
	int I2CBus;
	SlaveDevice slave;
	int8_t readI2CByte(int8_t);
	bool writeI2CByte(int8_t, int8_t);
	void servoControllerReset();
	int map(int, int, int, int, int);	// maps angle values from deg to pwm value

public:
	AdaFruitServoDriver(int);
	AdaFruitServoDriver(int, int8_t);
	bool initializeServoDriver(int);
	bool setPWMValue(int8_t, int16_t);
	~AdaFruitServoDriver();
};

#endif /* ADAFRUITSERVODRIVER_H_ */
