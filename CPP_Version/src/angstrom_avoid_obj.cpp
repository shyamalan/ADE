/*
 * I2CServoDriver.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: kartik
 */

#include <iostream>
#include "Hexapod.h"


using namespace std;


int main(){
	Hexapod *robot = new Hexapod();
	robot -> walkFwd(2);
	return 0;
}
