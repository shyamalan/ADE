#include <iostream>
#include "AdaFruitServoDriver.h"

using namespace std;

#define INCREMENT_ARM 2
#define DELAY 20
#define SERVOMIN_ARM 200
#define SERVOMAX_ARM 630

class arm {
private:
	int pinNo[4];
	int min_angle[4];
	int max_angle[4];
	int current_angle[4];
	
	float pi;
	int offset[3];
	
	void goto_position (float[], bool);
	void get_DOFs (float[], float[]);
	int map(float, float, float, float, float);

public:
	void goto_XYZ(float[], bool);
	arm();
};
