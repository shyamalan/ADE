/*
 * adaFruitDriver.c
 *
 *  Created on: Nov 1, 2013
 *      Author: kartik
 */

#include "adaFruitDriver.h"

void servoControllerReset(int8_t i2caddr) {
	writeI2CByte(i2caddr, PCA9685_MODE1, 0x0);
}

void setPWMValue(int i2cBus, int8_t i2caddr, int8_t num, int16_t pwmValue){
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
	I2CBus = i2cBus;
	initializeServoDriver(60, i2caddr);
	int8_t startAddr = LED0_ON_L + 4 * num;
	char buffer[5];

	buffer[0] = startAddr;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = pwmValue;
	buffer[4] = pwmValue >> 8;
	accept(I2CBus, i2caddr, buffer, 5);
}

void initializeServoDriver(int freq, int8_t i2caddr){
	servoControllerReset(i2caddr);
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

	int8_t oldmode = readI2CByte(i2caddr,PCA9685_MODE1);
	int8_t newmode = (oldmode & 0x7F) | 0x10; 			// disable restart and switch oscillator off
	writeI2CByte(i2caddr, PCA9685_MODE1, newmode); 		// go to sleep
	writeI2CByte(i2caddr, PCA9685_PRESCALE, prescale); 	// set the prescaler
	writeI2CByte(i2caddr, PCA9685_MODE1, oldmode);

	sleep(0.5);											// wait

	writeI2CByte(i2caddr, PCA9685_MODE1, oldmode | 0xa1); 		// enable restart,

}

int8_t readI2CByte(int8_t i2caddr, int8_t addr){
	char buffer;
	reveal(I2CBus, i2caddr, 1, &buffer);
	return (int8_t)buffer;
}


void writeI2CByte(int8_t i2caddr, int8_t regAddr, int8_t value){
	char buffer[2];
	buffer[0] = (char)regAddr;
	buffer[1] = (char)value;
	accept(I2CBus,i2caddr, buffer, 2);
}


