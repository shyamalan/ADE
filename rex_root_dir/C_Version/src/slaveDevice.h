/*
 * slaveDevice.h
 *
 *  Created on: Nov 1, 2013
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
#include <stdint.h>

int file;

void beginCommunication(int8_t, int8_t);
void reveal(int8_t, int8_t, int, char*);
void accept(int8_t, int8_t, char[], int);
void endCommunication();

#endif /* SLAVEDEVICE_H_ */
