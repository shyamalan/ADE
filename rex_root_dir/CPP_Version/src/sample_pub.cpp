#include "pubsub.h"
#include "Serial.h"
#include <iostream>

using namespace std;
bool setup() {
        return true;
}

char dist[1];
bool loop() {
	key_t key = 1234;
	if (!kbhit()) {
		dist[0] = (char) 10;
		return publish(key, dist, 1);
	}
	else{
		endTransfer(key);
		return false;
	}
}
