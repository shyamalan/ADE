#include <iostream>
#include "Serial.h"
#include "pubsub.h"
#include <string.h>

key_t task_key, key_master = 1234;
key_t key[2];
char* key_stroke;

bool setup(){
	key_stroke[0] = 0;
	return true;
}

char name[10] = "defalt";

bool loop(){
	if(!kbhit()){
		char *data;
		subscribe(key_master, data, 7);
                task_key = keygen(data);
		if(data[5] == 's'){
			key[0] = task_key;
			subscribe(task_key, key_stroke, 1);
		}
		else if(data[5] = 'p'){
			key[1] = task_key;
			publish(task_key, key_stroke, 1);
		}
	}
	else{
		endTransfer(key[0]);
		endTransfer(key[1]);
	}
}

