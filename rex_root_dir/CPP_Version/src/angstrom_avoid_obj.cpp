/*
 * I2CServoDriver.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: kartik
 */

#include <iostream>
#include "Hexapod.h"
#include "Serial.h"
#include "pubsub.h"
#include <string.h>

using namespace std;

key_t key;
char name[7];
Hexapod robot;
//char UP, DOWN, LEFT, RIGHT;
bool setup() {
	strcpy(name, "wire1s");
	key = keygen(name);
	robot.Hexapod_init();
/*	cout << "Press the UP key" << endl;
	UP = getchar();
	cout << "UP key registered" << endl;
	cout << "Press the DOWN key" << endl;
	DOWN = getchar();
	cout << "DOWN key registered" << endl;
	cout << "Press the LEFT key" << endl;
	LEFT = getchar();
	cout << "LEFT key registered" << endl;
	cout << "Press the RIGHT key" << endl;
	RIGHT = getchar();
	cout << "RIGHT key registered" << endl;
	cout << "Begin you moves";*/
	return true;
}

char data[1];
bool loop(){
	beginComm(name);
	if(subscribe(key, data, 1)){
//		char ch = getchar();
		if (data[0] == 'w'){
			robot.walkFwd(1);
			return true;
		}
		if (data[0] == 's'){
			robot.walkFwd(-1);    
                        return true;
		}
		if (data[0] == 'a'){
			robot.walkSide(1);     
                        return true;
		}
		if (data[0] == 'd'){
			robot.walkSide(-1);    
                        return true;
		}
		if (data[0] == 'c'){
			cout << "end" << endl;
			robot.reliefStep();
			endTransfer(key); 
                        return false;
		}
	}
	return true;
}

