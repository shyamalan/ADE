#include <iostream>
#include "Serial.h"

using namespace std;

bool Setup(){
	cout << "Enter any key" << endl;
}

bool loop(){
	if (kbhit()){
		cout << (char)getchar() << " key has been hit" << endl;
		return false;
	}
	return true;
}

