#include "rangeFinder.h"

using namespace std;

rangeFinder :: rangeFinder(bool cm){
	char *buffer = new char;
	buffer[0] = 0x00;
	if (cm)
		buffer[1] = 0x51;
	else
		buffer[1] = 0x50;
	slave.init_device(I2CBus, I2CAddress);
	slave.accept(buffer, 2);
	usleep(70 * 1000);
}

int rangeFinder :: dist(){
	char *buffer = new char;
	slave.reveal((int8_t)0x02, 2, buffer);
	range = ((int8_t) buffer[0]<< 8) + (int8_t) buffer[1];
	return range;
}

rangeFinder :: ~rangeFinder(){
}
