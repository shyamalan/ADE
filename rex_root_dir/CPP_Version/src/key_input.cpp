#include "pubsub.h"
#include <iostream>
#include "Serial.h"
#include "pubsub.h"
#include <string.h>

using namespace std;

key_t key;
char name[7];
bool setup() {
	char name[3];
	strcpy(name, "wire1p");
	key = keygen(name);
	return true;
}
char data[1];
bool loop() {
	beginComm(name);
	if(kbhit()) {
		data[0] = getchar();
		//cout << data[0];
		publish(key, data, 1);
		if(data[0] == 'c')
			return false;
	}
	return true;
}
