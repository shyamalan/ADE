/*
 * SlaveDevice.h
 *
 *  Created on: Aug 20, 2013
 *      Author: kartik
 */

#ifndef SLAVEDEVICE_H_
#define SLAVEDEVICE_H_

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <unistd.h>


#define MAX_BUS 64

using namespace std;


class SlaveDevice{
private:
	int I2CBus;
	int8_t I2CAddress;
	int file;
	bool beginCommunication();
	void endCommunication();
public:
	void init_device(int, int8_t);
	bool reveal(int8_t, int, char*);
	bool accept(char*, int);
};



#endif /* SLAVEDEVICE_H_ */
