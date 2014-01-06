/*
 * SlaveDevice.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: kartik
 */

#include <iostream>
#include "SlaveDevice.h"

void SlaveDevice :: beginCommunication(int8_t I2CBus, int8_t I2CAddress){
	char name[MAX_BUS];
	sprintf(name, "/dev/i2c-%d", I2CBus);
	if ((file = open(name, O_RDWR)) < 0){
		cout << "Failed to open the device on " << name << " I2C Bus" << endl;
	}
	if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
		cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
	}
}

void SlaveDevice :: reveal(int8_t I2CBus, int8_t I2CAddress, int numOfBytes, char* data){
	beginCommunication(I2CBus, I2CAddress);
	int8_t buf[1] = { 0x00 };
	if(write(file, buf, 1) != 1){
		cout << "Failed to set read mode" << endl;
	}
	if(read(file, data, numOfBytes) != numOfBytes){
		cout << "Failed to read from the slave" << endl;
	}
	close(file);
}

void SlaveDevice :: accept(int8_t I2CBus, int8_t I2CAddress, char data[], int size){
	beginCommunication(I2CBus, I2CAddress);
	if(write(file, data, size) != size)
		cout << "Failed to write to slave" << endl;
	close(file);
}

