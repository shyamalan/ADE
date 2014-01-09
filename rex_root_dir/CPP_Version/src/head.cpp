#include "Serial.h"
#include <iostream>
#include "AdaFruitServoDriver.h"
include "pubsub.h"

using namespace std;

AdaFruitServoDriver driver;
key_t key;
int8_t pinNo = 0;
int rev = -1;
int fwd = 1;

bool setup(){
	key = 1234;
	driver.begin(0x40);
	return driver.initializeServoDriver(60);
}

bool loop(){
	if(!kbhit()){
		char *pos;
		subscribe(key, pos, 2);
		if(pos[0] > 0)
			driver.setPWMValue(PinNo, rev);
		else if(pos[0] < 0)
			driver.setPWMValue(pinNo, fwd);
		return true;
	}
	else{
		endTransmission(key);
		return false;
	}
}

