
#include <iostream>
#include "Serial.h"
#include "face.h"
#include "pubsub.h"

using namespace std;

bool setup() {
	return true;
}

bool loop(){
	key_t key = 1234;
	if(!kbhit()){ \\ true till it encounters a keyboard hit
		cout << endl << "Number of faces = " << detect() << endl;
		char *pos;
		pos = face_pos();
		publish(key, pos, 2);
		return true;
	}
	else{
		return false;
	}
}

