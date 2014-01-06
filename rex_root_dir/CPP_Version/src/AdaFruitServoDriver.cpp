/*
 * AdaFruitServoDriver.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: kartik
 */

#include "AdaFruitServoDriver.h"
#include <iostream>

using namespace std;

AdaFruitServoDriver :: AdaFruitServoDriver(int i2cBus) {
	I2CAddress = 0x40;
	I2CBus = i2cBus;
	slave.init_device(I2CBus, I2CAddress);
	servoControllerReset();
}

AdaFruitServoDriver :: AdaFruitServoDriver(int i2cBus, int8_t i2caddr) {
	I2CAddress = i2caddr;
	I2CBus = i2cBus;
	slave.init_device(I2CBus,I2CAddress);
	servoControllerReset();
}

void AdaFruitServoDriver :: servoControllerReset() {
	writeI2CByte(PCA9685_MODE1, 0x0);
}

bool AdaFruitServoDriver :: setPWMValue(int8_t num, int16_t pwmValue){
	/*
	 * The sequence of data transfer is (if the control registers are in sequence):
	 * 1: address of the first control register.
	 * 2: value to be written in the first register.
	 * .....
	 * n: value to be written in the (n-1)th register after the first one.
	 *
	 * Each register can have 1 byte of data and after each R/W operation the register
	 * in auto incremented.
	 */

	int8_t startAddr = LED0_ON_L + 4 * num;
	char buffer[5];

	buffer[0] = startAddr;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = pwmValue;
	buffer[4] = pwmValue >> 8;
	return slave.accept(buffer, 5);
}

bool AdaFruitServoDriver :: initializeServoDriver(int freq){
	/*
	 * According to the data sheet the value of prescale and the EXTCTL are related (pg. 13)
	 * Following calculation assumes the EXTCTL to be 25MHz (because the manufacturer used this
	 * value for Arduino and the RPi library)
	 */
	float prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	int8_t prescale = floor(prescaleval + 0.5);

	/*
	 * To restart the device following sequence has to be followed:
	 * 1: Bit 7 (RESTART) of MODE1 is put to LOW (disabled)
	 * 2: Bit 4 (SLEEP) of MODE1 is put to HIGH (Low power mode)
	 * 3: Wait for at least 500 micro seconds
	 * 4: Bit 7 of MODE1 is put to HIGH (enabled)
	 *
	 * Bit 5 (AI) of MODE1 is put to HIGH to enable auto-increment mode
	 */
	int8_t oldmode = readI2CByte(PCA9685_MODE1);
	int8_t newmode = (oldmode & 0x7F) | 0x10; 	// disable restart and switch oscillator off
	if(!writeI2CByte(PCA9685_MODE1, newmode)){ 		// go to sleep
		return false;
	}
	if(!writeI2CByte(PCA9685_PRESCALE, prescale)){ 	// set the prescaler
		return false;
	}
	if(!writeI2CByte(PCA9685_MODE1, oldmode)){
		return false;
	}
	sleep(0.5);									// wait

	if(!writeI2CByte(PCA9685_MODE1, oldmode | 0xa1)){ // enable restart
		return false;
	}
	return true;

}

int8_t AdaFruitServoDriver :: readI2CByte(int8_t addr){
	char buffer[1];
	if(slave.reveal(addr, 1, buffer)){
		return (int8_t)buffer[0];
	}
	return (int8_t)0;
}


bool AdaFruitServoDriver :: writeI2CByte(int8_t regAddr, int8_t value){
	char buffer[2];
	buffer[0] = (char)regAddr;
	buffer[1] = (char)value;
	return slave.accept(buffer, 2);
}

AdaFruitServoDriver :: ~AdaFruitServoDriver(){
}
