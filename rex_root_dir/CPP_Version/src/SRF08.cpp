/*
 * SRF08.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: Mike Lewis (mikelewis@alphalem.com)
 */

#include "SRF08.h"
#include <iostream>

using namespace std;

SRF08 :: SRF08(int i2cBus) {
	I2CAddress = DEFAULT_ADDR;
	I2CBus = i2cBus;
	slave.init_device(I2CBus, I2CAddress);
}

SRF08 :: SRF08(int i2cBus, int8_t i2caddr) {
	I2CAddress = i2caddr;
	I2CBus = i2cBus;
	slave.init_device(I2CBus,I2CAddress);
}

// Returns the distance measurement buffer in raw form
int8_t* SRF08 :: getRange(int8_t units) {
	initRanging(units);

	// This means that the sensor is "busy"
	while (readI2CByte(COMMAND_REG) == 0xFF);

	// For now, only returns the distance data in raw form (based on echos)
	// TODO: extend the buffer to include all echos (1-17)
	int8_t buf[2];
	buf[0] = readI2CByte(ECHO_1_HI);
	buf[1] = readI2CByte(ECHO_1_LO);
	return buf;
}

// Returns the current light level as measured by the light sensor
int8_t SRF08 :: getLight() {
	return readI2CByte(LIGHT);
}

// Once ranging is initiated (given desired units for ret_value), the SRF08
// will stop responding to the I2C bus until it is complete.
void SRF08 :: initRanging(int8_t units) {
	writeI2CByte(COMMAND_REG, units);
}

int8_t SRF08 :: readI2CByte(int8_t addr) {
	char buffer[1];
	if (slave.reveal(addr, 1, buffer)) {
		return (int8_t)buffer[0];
	}
	return (int8_t)0;
}


bool SRF08 :: writeI2CByte(int8_t regAddr, int8_t value) {
	char buffer[2];
	buffer[0] = (char)regAddr;
	buffer[1] = (char)value;
	return slave.accept(buffer, 2);
}

SRF08 :: ~SRF08() {
}
