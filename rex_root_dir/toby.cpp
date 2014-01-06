/*
 * toby.cpp
 *
 * This brings toby to life.
 * Use it wisely.
 */

#include <iostream>
#include "Hexapod.h"
#include <unistd.h>

using namespace std;

int main(){
	//for vengeance
	kick_the_mug();
	return 0;
}

bool kick_the_mug(){
	Hexapod *robot = new Hexapod();
	sleep(7);
	robot -> walkFwd(5);
	usleep(500 * 1000);
	robot -> turn(-5);
	robot -> reliefStep();
	float pos[3] = {2.0, 3.5, 0.0}; 
	robot -> move_single_leg(6, pos);
	pos[0] += 2.5;
	pos[1] += 2.5;
	usleep(500 * 1000);
	robot -> move_single_leg(6, pos);
	usleep(500 * 1000);
	robot -> stand_pos(-4.0);
	delete robot;
	return true;
}


