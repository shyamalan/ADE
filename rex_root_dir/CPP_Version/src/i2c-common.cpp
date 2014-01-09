/*
 * SlaveDevice.cpp
 *
 *  Created on: Aug 20, 2013
 *      Author: kartik
 */

#include <iostream>
#include "i2c-common.h"
void SlaveDevice :: init_device(int i2cBus, int8_t i2caddr){
	I2CBus = i2cBus;
	I2CAddress = i2caddr;
}
bool SlaveDevice :: beginCommunication(){
	char name[MAX_BUS];
	sprintf(name, "/dev/i2c-%d", I2CBus);
	if ((file = open(name, O_RDWR)) < 0){
		cout << "Failed to open the device on " << name << " I2C Bus" << endl;
		return false;
	}
	if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
		cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
		return false;
	}
	return true;
}

bool SlaveDevice :: reveal(int8_t addr, int numOfBytes, char* data){
	beginCommunication();
	int8_t buffer[1] = { addr };
	if(write(file, buffer, 1) != 1){
		cout << "Failed to set read mode" << endl;
		return false;
	}
	if(read(file, data, numOfBytes) != numOfBytes){
		cout << "Failed to read from the slave" << endl;
		return false;
	}
	close(file);
	return true;
}

bool SlaveDevice :: accept(char *data, int size){
	beginCommunication();
	if(write(file, data, size) != size){
		cout << "Failed to write to slave" << endl;
		return false;
	}
	close(file);
	return true;
}

void SlaveDevice :: endCommunication(){
	close(file);
}

