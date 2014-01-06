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
	int file;
	void beginCommunication(int8_t, int8_t);

public:
	void reveal(int8_t, int8_t, int, char*);
	void accept(int8_t, int8_t, char[], int);
	void endCommunication();
};



#endif /* SLAVEDEVICE_H_ */
