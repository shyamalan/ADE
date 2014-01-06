#include "pubsub.h"
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
	if(kbhit()) {
		data[0] = getchar();
		cout << data[0];
		return publish(key, data, 1);
	}
	return true;
}
