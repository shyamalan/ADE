/*
 * toby.c
 *
 *  Created on: Nov 1, 2013
 *      Author: kartik
 */

#include <stdio.h>
#include "hexapod.h"
#include "slaveDevice.h"

int main(){
	int8_t I2CAddress = 0x04, I2CBus = 2;
//	int sensorValue_us = 0;
//	char buffer;
	init_hexapod();
/*	while(true){
		reveal(I2CBus, I2CAddress, 2, &buffer);
		sensorValue_us = 256 * (int)buffer[1] + (int) buffer[0];
//		sensorValue_ir = 256 * (int)buffer[3] + (int) buffer[2];
		printf("%i\n",sensorValue_us);
		if (sensorValue_us < 30)
			turn(3);
		else
			walkFwd(1);
	}*/
	walkFwd(1);
	return 0;
}


