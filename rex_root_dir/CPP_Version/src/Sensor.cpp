/*
 * I2CServoDriver.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: kartik
 */

#include <iostream>
#include "Serial.h"
#include "MMA7455.h"
using namespace std;

MMA7455 device;
bool setup() {
	return device.begin();
}

bool loop(){
	if(!kbhit()){
		cout << device.acc_x() << endl;
		return true;
	}
	else{
		device.end();
		return false;
	}
}

