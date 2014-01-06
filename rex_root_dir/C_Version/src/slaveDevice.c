/*
 * slaveDevice.c
 *
 *  Created on: Nov 1, 2013
 *      Author: kartik
 */

#include "slaveDevice.h"

#define MAX_BUS 64

void beginCommunication(int8_t I2CBus, int8_t I2CAddress){
	char name[MAX_BUS];
	sprintf(name, "/dev/i2c-%d", I2CBus);
	if ((file = open(name, O_RDWR)) < 0){
		printf("Failed to open the device on %s I2C Bus\n", name);
	}
	if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
		printf("Connection with I2C SLAVE address %i failed ...\n", I2CAddress);
	}
}

void reveal(int8_t I2CBus, int8_t I2CAddress, int numOfBytes, char data[]){
	beginCommunication(I2CBus, I2CAddress);
	int8_t buf[1] = { 0x00 };
	if(write(file, buf, 1) != 1){
		printf("Failed to set read mode\n");
	}
	if(read(file, data, numOfBytes) != numOfBytes){
		printf("Failed to read from the slave device\n");
	}
	close(file);
}

void accept(int8_t I2CBus, int8_t I2CAddress, char data[], int size){
	beginCommunication(I2CBus, I2CAddress);
	if(write(file, data, size) != size)
		printf("Failed to write to slave\n");
	close(file);
}


