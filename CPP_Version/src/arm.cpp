#include "arm.h"

AdaFruitServoDriver *driver = new AdaFruitServoDriver(0x41, 2);

arm :: arm (){
	min_angle[0] = 60;
	min_angle[1] = 60;
	min_angle[2] = 10;
	min_angle[3] = 30;
	max_angle[0] = 140;
	max_angle[1] = 175;
	max_angle[2] = 180;
	max_angle[3] = 120;
	
	pinNo[0] = 9;
	pinNo[1] = 10;
	pinNo[2] = 11;
	pinNo[3] = 12;
	
	pi = 3.14;
	
	offset[0] = 10;
	offset[1] = -5;
	offset[2] = 23;
	
	driver -> initializeServoDriver(60);
	
	for (int i = 0; i < 4; i++){
		int pwmValue = map(min_angle[i], 0, 180, SERVOMIN_ARM, SERVOMAX_ARM);
		driver -> setPWMValue(pinNo[i], pwmValue);
		current_angle[i] = min_angle[i];
	}
	sleep(1);
}

void arm :: goto_XYZ (float pos[], bool grab){
	float angle[3];
	get_DOFs (pos, angle);
	for(int i = 0; i < 3; i++)
		cout << angle[i] << endl;
	goto_position (angle, grab);
}

void arm :: get_DOFs (float pos[], float angle[]){
	angle[0] = atan(pos[1]/ pos[0]) * 180 / pi;
	angle[0] = 90 - angle[0] + offset[0];
	
	float G = pow((pow(pos[0], 2) + pow(pos[1], 2)), (float) 0.5);
  
//	float alpha = atan(34.6 / 48) * 180 / pi;
	float beta = atan((pos[2] - 6.2) / (G - 11)) * 180 / pi;
	
	float H = pow( (pow( (pos[2] - 6.2), 2 ) + pow( (G - 11), 2 ) ), (float) 0.5 );
	float A = pow((pow(50, 2) + pow(34.6, 2)), (float) 0.5);

	angle[2] = (pow(A, 2) + pow(46, 2) - pow(H, 2)) / (2 * A * 46);
	angle[2] = acos(angle[2]) * 180 / pi;
	angle[2] = 180 - angle[2] + offset[2];
	
	angle[1] = (pow(H, 2) + pow(46, 2) - pow(A, 2)) / (2 * H * 46);
	angle[1] = acos(angle[1]) * 180 / pi;
	angle[1] = 90 + angle[1] + beta + offset[1];
}

void arm :: goto_position (float angle[], bool grab){
	bool flag = true;
	while (flag)
	{
		flag = false;
		int des_angle;
		for(int i = 0; i < 3; i++){
			int inc = INCREMENT_ARM;
			if((current_angle[i] - angle[i]) >= INCREMENT_ARM || (current_angle[i] - angle[i]) <= -1 * INCREMENT_ARM){
				if(angle[i] < current_angle[i])
					inc = inc * -1;
				des_angle = current_angle[i] + inc;

				int pwmValue = map(des_angle, 0, 180, SERVOMIN_ARM, SERVOMAX_ARM);
				driver -> setPWMValue(pinNo[i], pwmValue);
				current_angle[i] = des_angle;
				flag = true;
			}
		}
		usleep(DELAY * 1000);
	}
	cout << "Done" << endl;
	if(grab){
		for(int i = current_angle[3]; i < 120;){
			int pwmValue = map(i, 0, 180, SERVOMIN_ARM, SERVOMAX_ARM);
			driver -> setPWMValue(pinNo[3], pwmValue);
			current_angle[3] = i;
			i = i + INCREMENT_ARM;
			usleep(DELAY * 1000);
		}
	}
	
	else{
		for(int i = current_angle[3]; i > 30;){
			int pwmValue = map(i, 0, 180, SERVOMIN_ARM, SERVOMAX_ARM);
			driver -> setPWMValue(pinNo[3], pwmValue);
			current_angle[3] = i;
			i = i - INCREMENT_ARM;
			usleep(DELAY * 1000);
		}
	}
  
	cout << "Done" << endl;
}

int arm :: map (float var, float fromMin, float fromMax, float toMin, float toMax){

	int value = 0;
	int toDiff = 0, fromDiff = 0;
	toDiff = toMax - toMin;
	fromDiff = fromMax - fromMin;
	value = (var * ((float)toDiff / (float)fromDiff));
	return (toMin + value);
}
