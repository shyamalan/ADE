#include <iostream>
#include "Serial.h"
#include "pubsub.h"

using namespace std;

bool setup() {
	return true;
}

char data[1];
bool loop() {
	key_t key = 1234;
//	if(!kbhit()){
		bool flag = subscribe(key, data, 1);
		cout << (int)data[0] << endl;
		return flag;
/*	}
	else{
		endTransfer(key);
		return false;
	}*/
}
