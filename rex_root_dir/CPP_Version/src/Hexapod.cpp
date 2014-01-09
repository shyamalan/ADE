/*
 * Hexapod.cpp
 *
 *  Created on: Aug 18, 2013
 *      Author: kartik
 */
#include "Hexapod.h"

using namespace std;

void Hexapod :: Hexapod_init(){
	driver1.begin(0x40);
	driver2.begin(0x41);
	HEIGHT = -4.0;
	prob = true;
	if(!driver1.initializeServoDriver(60))
		prob = false;
	if(!driver2.initializeServoDriver(60))
		prob = false;
	// initialization of angle of each leg's co-ordinate system
	alpha[0] = 60;
	alpha[1] = 0;
	alpha[2] = -60;
	alpha[3] = 120;
	alpha[4] = 180;
	alpha[5] = -120;

	home_value[0] 	= HOME_1;
	home_value[1] 	= HOME_2;
	home_value[2] 	= HOME_3;
	home_value[3] 	= HOME_4;
	home_value[4] 	= HOME_5;
	home_value[5] 	= HOME_6;
	home_value[6] 	= HOME_7;
	home_value[7] 	= HOME_8;
	home_value[8] 	= HOME_9;
	home_value[9] 	= HOME_10;
	home_value[10] 	= HOME_11;
	home_value[11] 	= HOME_12;
	home_value[12] 	= HOME_13;
	home_value[13] 	= HOME_14;
	home_value[14] 	= HOME_15;
	home_value[15] 	= HOME_16;
	home_value[16] 	= HOME_17;
	home_value[17] 	= HOME_18;

	for(int i = 0; i < 18; i++){
		int pwmValue = 0, value = home_value[i];

		// to prevent from sudden falling
		if(i < 7 && i % 3 == 0)
			value = home_value[i] + 90;

		if(i > 7 && i % 3 == 0)
			value = home_value[i] - 90;

		pwmValue = map(value, 0, 180, SERVOMIN, SERVOMAX);
		if(i < 9){
			if(!driver1.setPWMValue(i, pwmValue))
				prob = false;
		}
		else{
			if(!driver2.setPWMValue(i - 9, pwmValue))
				prob = false;
		}
		// update the current value of the angle
		if(i < 7 && i % 3 == 0)
			value = 90;
		else if(i > 7 && i % 3 == 0)
			value = 0;
		else
			angle[i] = 0;

		des_angle[i] = 0;

		angle_inc[i] = INCREMENT;

		// each elbow DOF has a negative rotation axis
		if(i % 3 == 1)
			dir_rot[i] = -1;
		else
			dir_rot[i] = 1;
	}
	usleep(1000 * 1000);
	init_stand(HEIGHT); // initiate the standing position
	for(int i = 0; i < 18; i++)
	stand[i] = des_angle[i];
	moveToDOFValue();
}

bool Hexapod :: moveToDOFValue(){
	int threshold = THRESHOLD;
	bool position_reached = false;

	while(!position_reached){
		int count = 0; //to exit the loop when destination is reached

		for(int i = 0; i < 18; i++){
			int pwmValue = 0;
			if((angle[i] - des_angle[i] <= -1 * threshold) || (angle[i] - des_angle[i] >= threshold)){
				if(des_angle[i] - angle[i] < 0)
					angle_inc[i] = -1 * threshold;

				// increment the angle
				angle[i] = angle[i] + angle_inc[i];

				// calculate the corresponding pwm value
				pwmValue = map((dir_rot[i] * angle[i] + home_value[i]), 0, 180, SERVOMIN, SERVOMAX);

				if(DOF_Limits()){
					if(i < 9){
						if(!driver1.setPWMValue(i, pwmValue))
							return false;
						usleep(DELAY2 * 1000);
					} // if statement end
					else{
						if(!driver2.setPWMValue((i - 9), pwmValue))
							return false;
						usleep(DELAY2 * 1000);
					} // else statement end
					count++;
				} // if statement end
				else{
					angle[i] -= angle_inc[i];
					position_reached = true;
					break;
				} // else statement end
			} // if statement end
		} // for loop end

		if(count == 0){
			position_reached = true;
			for(int i = 0; i < 18; i++)
				angle_inc[i] = INCREMENT;
		} // if statement end
	} // while loop end
	return true;
} // function end

void Hexapod :: setDOFValues(int DOFValues[]){
	for(int i = 0; i < 18; i++){
		des_angle[i] = DOFValues[i];
	} // for loop end
} // function end


void Hexapod :: stand_pos (float height) {
	init_stand(height);
	prob = moveToDOFValue();

}

void Hexapod :: rise(float h) {
	HEIGHT = -h;
	stand_pos(HEIGHT);
}

void Hexapod :: init_stand(float height){

	currentPos[0][0] = 2.0;
	currentPos[0][1] = 3.5;
	currentPos[0][2] = height;
	get_DOF(currentPos[0], 1);

	currentPos[1][0] = 0.0;
	currentPos[1][1] = 3.5;
	currentPos[1][2] = height;
	get_DOF(currentPos[1], 2);

	currentPos[2][0] = -2.0;
	currentPos[2][1] = 3.5;
	currentPos[2][2] = height;
	get_DOF(currentPos[2], 3);

	currentPos[3][0] = -2.0;
	currentPos[3][1] = 3.5;
	currentPos[3][2] = height;
	get_DOF(currentPos[3], 4);

	currentPos[4][0] = 0.0;
	currentPos[4][1] = 3.5;
	currentPos[4][2] = height;
	get_DOF(currentPos[4], 5);

	currentPos[5][0] = 2.0;
	currentPos[5][1] = 3.5;
	currentPos[5][2] = height;
	get_DOF(currentPos[5], 6);

	for(int i = 0; i < 18; i++)
		stand[i] = des_angle[i];
} // function end

void Hexapod :: get_DOF(float pos[3], int legNo){
	float pos_origin[4];
	// position vector
	for(int i = 0; i < 4; i++){
		if(i < 3)
		  pos_origin[i] = pos[i];
		else
		  pos_origin[i] = 1;
	} // for loop end

	//theta_3 = atan(X / Y)
	float theta_3 = atan(pos_origin[0] / pos_origin[1]);
	des_angle[3 * legNo - 1] = -1 * 180 * theta_3 / pi;

	float pos_2[2];
	pos_2[0] = pos_origin[2] - z_1_2;
	pos_2[1] = pow(pos_origin[0], 2) + pow(pos_origin[1], 2);
	pos_2[1] = pow(pos_2[1], (float) 0.5) - y_1_2; // relative to co-ordinates of the elbow joint

	float H = pow(pos_2[0], 2) + pow(pos_2[1], 2);
	H = pow(H, (float) 0.5);

	float alpha = pi / 2;
	alpha = alpha + atan(x_3_ee / y_3_ee);

	float theta_1 = 0.0;
	float length1 = pow(x_3_ee, 2) + pow(y_3_ee, 2);
	length1 = pow(length1 , (float) 0.5);

	theta_1 = (pow(length1, 2) + pow(x_2_3, 2) - pow(H, 2)) / (2 * length1 * x_2_3);
	theta_1 = acos(theta_1);
	theta_1 = alpha - theta_1;

	float beta = asin(pos_2[0] / H);
	float theta_2 = (pow(x_2_3, 2) + pow(H, 2) - pow(length1, 2)) / (2 * x_2_3 * H);
	theta_2 = acos(theta_2);
	theta_2 = theta_2 + beta;
	theta_2 = (pi / 2) - theta_2;

	des_angle[3 * legNo - 3] = 180 * theta_1 / pi;
	des_angle[3 * legNo - 2] = 180 * theta_2 / pi;

	// directions gets reversed for the right side of the robot
	if(legNo > 3){
		des_angle[3 * legNo - 1] = -1 * des_angle[3 * legNo - 1];
		des_angle[3 * legNo - 2] = -1 * des_angle[3 * legNo - 2];
		des_angle[3 * legNo - 3] = -1 * des_angle[3 * legNo - 3];
	} // if statement end
} // function end


bool Hexapod :: DOF_Limits(){

	for(int i = 0; i < 18; i++){
		float pwmValue = map((dir_rot[i] * angle[i] + home_value[i]), 0, 180, SERVOMIN, SERVOMAX);
		// check for joints being within limits
		if((pwmValue > SERVOMAX) || (pwmValue < SERVOMIN)){
				cout << "Joint No. " << i + 1 << " is beyond its DOF limit." << endl;
				return false;
		} // if statement end
	} // foe loop end
	return true;
} // function end


bool Hexapod :: walkFwd(int numOfSteps){

//	cout << "The Hexapod will walk " << numOfSteps << " steps" << endl;
	prob = true;
	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepFwd1[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_fwd(true, (walk_dir * WALK_DISTANCE / 2));
	for(int i = 0; i < 18; i++)
		stepFwd2[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepFwd3[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_fwd(false, (walk_dir * WALK_DISTANCE));
	for(int i = 0; i < 18; i++)
		stepFwd4[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(int i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepFwd1);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepFwd2);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepFwd3);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepFwd4);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand(HEIGHT);			// return to home position
	prob = moveToDOFValue();
//	cout << "Done" << endl;
	return prob;
}

bool Hexapod :: walkSide(int numOfSteps){
//	cout << "The Hexapod will walk " << numOfSteps << " steps to the side" << endl;
	prob = true;
	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepSide1[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_side(true, (walk_dir * WALK_DISTANCE / 2));
	for(int i = 0; i < 18; i++)
		stepSide2[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepSide3[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_side(false, (walk_dir * WALK_DISTANCE));
	for(int i = 0; i < 18; i++)
		stepSide4[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(int i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepSide1);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepSide2);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepSide3);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepSide4);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand(HEIGHT);			// return to home position
	prob = moveToDOFValue();
//	cout << "Done" << endl;
	return prob;
}

bool Hexapod :: turn(int numOfSteps){
//	cout << "The Hexapod will turn " << numOfSteps << " steps" << endl;
	prob = true;
	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepTurn1[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_turn(true, (walk_dir * 10));
	for(int i = 0; i < 18; i++)
		stepTurn2[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepTurn3[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_turn(false, (walk_dir * 10));
	for(int i = 0; i < 18; i++)
		stepTurn4[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(int i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepTurn1);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepTurn2);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepTurn3);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepTurn4);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand(HEIGHT);			// return to home position
	prob = moveToDOFValue();
//	cout << "Done" << endl;
	return prob;
}

bool Hexapod :: walkCombined(float angle, int numOfSteps){
//	cout << "The Hexapod will walk " << numOfSteps << " steps diagonally" << endl;
	prob = true;
	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepComb1[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_comb(true, (walk_dir * WALK_DISTANCE / 2), angle);
	for(int i = 0; i < 18; i++)
		stepComb2[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(int i = 0; i < 18; i++)
		stepComb3[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_comb(false, (walk_dir * WALK_DISTANCE), angle);
	for(int i = 0; i < 18; i++)
		stepComb4[i] = des_angle[i];
	prob = moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(int i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepComb1);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepComb2);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepComb3);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepComb4);
		prob = moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand(HEIGHT);			// return to home position
	prob = moveToDOFValue();
//	cout << "Done" << endl;
}

bool Hexapod :: move_single_leg(int legNo, float pos[]){
	get_DOF(pos, legNo);
	prob = moveToDOFValue();
}


void Hexapod :: leg_up(bool left_leg, float height){
	if(left_leg){
		for(int i = 0; i < 3; i++){
		  currentPos[2 * i][2] += height; 		// increment the current position of the end effector in z-axis
		  get_DOF(currentPos[2 * i], 2 * i + 1);
		} // for loop end
	} // if statement end
	else{
		for(int i = 0; i < 3; i++){
			currentPos[2 * i + 1][2] += height;
		get_DOF(currentPos[2 * i + 1], 2 * i + 2);
		} // for loop end
	}// else statement end
} // function end

void Hexapod :: leg_fwd(bool flag, float walkDistance){
	/*
	 * This function is constructed keeping in mind the fact that putting a leg forward
	 * consists of alternate legs going in opposite direction e.g when legNo 0, 2 and 4
	 * move forward the other three have to move back for smooth transition. Since the
	 * orientation of the legs on the right side of the robot is opposite to that on the
	 * left side, forward on one side is backward on the other side (hence leg no 0, 2, 3
	 * and 5 are clubbed together)
	 * The final procedure is to put the forward legs down
	 */

	if(flag){
		for(int legNo = 0; legNo < 6; legNo++){
			if(legNo == 0 || legNo == 2 || legNo == 3 || legNo == 5){
				currentPos[legNo][0] -= walkDistance * cos(alpha[legNo] * pi / 180);
				currentPos[legNo][1] += walkDistance * sin(alpha[legNo] * pi / 180);
			} // if statement end
			else{
				currentPos[legNo][0] += walkDistance * cos(alpha[legNo] * pi / 180);
				currentPos[legNo][1] -= walkDistance * sin(alpha[legNo] * pi / 180);
			} // else statement end
			if(legNo % 2 == 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;
			get_DOF(currentPos[legNo], legNo + 1);
		} // for loop end
	} // if statement end
	else{
		for(int legNo = 0; legNo < 6; legNo++){
			if(legNo == 0 || legNo == 2 || legNo == 3 || legNo == 5){
				currentPos[legNo][0] += walkDistance * cos(alpha[legNo] * pi / 180);
				currentPos[legNo][1] -= walkDistance * sin(alpha[legNo] * pi / 180);
			} // if statement end
			else{
				currentPos[legNo][0] -= walkDistance * cos(alpha[legNo] * pi / 180);
				currentPos[legNo][1] += walkDistance * sin(alpha[legNo] * pi / 180);
			} // else statement end
			if(legNo % 2 != 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;
			get_DOF(currentPos[legNo], legNo + 1);
		} // for loop end
	} // else statement end
} // function end

void Hexapod :: leg_side(bool flag, float walkDistance){
  if(flag){
    for(int legNo = 0; legNo < 6; legNo++){
      if(legNo % 2 == 0){
        currentPos[legNo][0] += walkDistance * sin(alpha[legNo] * pi / 180);
        currentPos[legNo][1] += walkDistance * cos(alpha[legNo] * pi / 180);
        currentPos[legNo][2] -= LEG_UP_HEIGHT;
      }
      else{
        currentPos[legNo][0] -= walkDistance * sin(alpha[legNo] * pi / 180);
        currentPos[legNo][1] -= walkDistance * cos(alpha[legNo] * pi / 180);
      }
      get_DOF(currentPos[legNo], legNo + 1);
    }
  }
  else{
    for(int legNo = 0; legNo < 6; legNo++){
      if(legNo % 2 == 0){
        currentPos[legNo][0] -= walkDistance * sin(alpha[legNo] * pi / 180);
        currentPos[legNo][1] -= walkDistance * cos(alpha[legNo] * pi / 180);
        get_DOF(currentPos[legNo], legNo + 1);
      }
      else{
        currentPos[legNo][0] += walkDistance * sin(alpha[legNo] * pi / 180);
        currentPos[legNo][1] += walkDistance * cos(alpha[legNo] * pi / 180);
        currentPos[legNo][2] -= LEG_UP_HEIGHT;
        get_DOF(currentPos[legNo], legNo + 1);
      }
    }
  }
}

void Hexapod :: leg_turn(bool flag, float turnAngle){
	if(flag){
		for(int legNo = 0; legNo < 6; legNo++){
			float theta_current = atan(currentPos[legNo][1] / currentPos[legNo][0]);
			float radius = pow(currentPos[legNo][0], 2) + pow(currentPos[legNo][1], 2);
			radius = pow(radius, (float)0.5);
			float theta_final = 0;

			if(legNo == 0 || legNo == 2 || legNo == 3 || legNo == 5){
				theta_final = theta_current + (turnAngle * pi / 180);
			}
			else{
				theta_final = theta_current - (turnAngle * pi / 180);
			}

			if(legNo % 2 == 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;

			currentPos[legNo][0] = radius * cos(theta_final);
			currentPos[legNo][1] = radius * sin(theta_final);
			get_DOF(currentPos[legNo], legNo + 1);
		}
	}
	else{
		for(int legNo = 0; legNo < 6; legNo++){
			float theta_current = atan(currentPos[legNo][1] / currentPos[legNo][0]);
			float radius = pow(currentPos[legNo][0], 2) + pow(currentPos[legNo][1], 2);
			radius = pow(radius, (float)0.5);
			float theta_final = 0;

			if(legNo == 1 || legNo == 4){
				theta_final = theta_current + (turnAngle * pi / 180);
			}
			else{
				theta_final = theta_current - (turnAngle * pi / 180);
			}

			if(legNo % 2 != 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;

			currentPos[legNo][0] = radius * cos(theta_final);
			currentPos[legNo][1] = radius * sin(theta_final);
			get_DOF(currentPos[legNo], legNo + 1);
		}
	}
}

void Hexapod :: leg_comb(bool flag, float walkDistance, float angle){
	angle = pi * angle / 180;
	leg_fwd(flag, (walkDistance * cos(angle)));
	leg_up(flag, LEG_UP_HEIGHT);
	leg_side(flag, (walkDistance * sin(angle)));
}

bool Hexapod :: reliefStep(){
	bool left_leg = true;

	// to reduce drag the legs have to do a relief procedure
	for(int i = 0; i < 2; i++){
		leg_up(left_leg, LEG_UP_HEIGHT);
		moveToDOFValue();
		leg_up(left_leg, -LEG_UP_HEIGHT);
		moveToDOFValue();
		left_leg = false;
	}
}

int Hexapod :: map (int var, int fromMin, int fromMax, int toMin, int toMax){

	int value = 0;
	int toDiff = 0, fromDiff = 0;
	toDiff = toMax - toMin;
	fromDiff = fromMax - fromMin;
	value = (var * ((float)toDiff / (float)fromDiff));
	return (toMin + value);
}

Hexapod :: ~Hexapod(){

}
