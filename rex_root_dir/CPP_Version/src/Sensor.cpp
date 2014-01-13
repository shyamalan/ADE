
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
	if(!kbhit()){ 
		cout << endl << "Number of faces = " << detect() << endl;
		float *pos;
		pos = face_pos();
		cout << pos[0] << pos[1] << endl;
		//publish(key, pos, 2);
		return true;
	}
	else{
		return false;
	}
}

