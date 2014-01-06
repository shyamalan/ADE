/*
 * hexapod.c
 *
 *  Created on: Nov 1, 2013
 *      Author: kartik
 */

#include "hexapod.h"


void init_hexapod(){

//	initializeServoDriver(60, DRIVER1, 2);
//	initializeServoDriver(60, DRIVER2, 2);
	PI = 3.14;
	
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

	int i;
	for(i = 0; i < 18; i++){
		int pwmValue = 0, value = home_value[i];

		// to prevent from sudden falling
		if(i < 7 && i % 3 == 0)
			value = home_value[i] + 90;

		if(i > 7 && i % 3 == 0)
			value = home_value[i] - 90;

		pwmValue = map(value, 0, 180, SERVOMIN, SERVOMAX);
		if(i < 9){
			setPWMValue(2, DRIVER1, i, pwmValue);
		}
		else{
			setPWMValue(2, DRIVER2, (i - 9), pwmValue);
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
	init_stand(); // initiate the standing position
	for(i = 0; i < 18; i++)
		stand[i] = des_angle[i];
	moveToDOFValue();
}

void moveToDOFValue(){
	int threshold = THRESHOLD;
	bool position_reached = false;

	while(!position_reached){
		int count = 0, i; //to exit the loop when destination is reached

		for(i = 0; i < 18; i++){
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
						setPWMValue(2, DRIVER1, i, pwmValue);
						usleep(DELAY2 * 1000);
					} // if statement end
					else{
						setPWMValue(2, DRIVER2, (i - 9), pwmValue);
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
			for(i = 0; i < 18; i++)
				angle_inc[i] = INCREMENT;
		} // if statement end
	} // while loop end
} // function end

void setDOFValues(int DOFValues[]){
	int i;
	for(i = 0; i < 18; i++){
		des_angle[i] = DOFValues[i];
	} // for loop end
} // function end

void init_stand(){

	currentPos[0][0] = 2.0;
	currentPos[0][1] = 3.5;
	currentPos[0][2] = -4.0;
	get_DOF(currentPos[0], 1);

	currentPos[1][0] = 0.0;
	currentPos[1][1] = 3.5;
	currentPos[1][2] = -4.0;
	get_DOF(currentPos[1], 2);

	currentPos[2][0] = -2.0;
	currentPos[2][1] = 3.5;
	currentPos[2][2] = -4.0;
	get_DOF(currentPos[2], 3);

	currentPos[3][0] = -2.0;
	currentPos[3][1] = 3.5;
	currentPos[3][2] = -4.0;
	get_DOF(currentPos[3], 4);

	currentPos[4][0] = 0.0;
	currentPos[4][1] = 3.5;
	currentPos[4][2] = -4.0;
	get_DOF(currentPos[4], 5);

	currentPos[5][0] = 2.0;
	currentPos[5][1] = 3.5;
	currentPos[5][2] = -4.0;
	get_DOF(currentPos[5], 6);
	
	int i;
	for(i = 0; i < 18; i++)
		stand[i] = des_angle[i];
} // function end

void get_DOF(float pos[3], int legNo){
	float pos_origin[4];
	// position vector
	int i;
	for(i = 0; i < 4; i++){
		if(i < 3)
		  pos_origin[i] = pos[i];
		else
		  pos_origin[i] = 1;
	} // for loop end

	//theta_3 = atan(X / Y)
	float theta_3 = atan(pos_origin[0] / pos_origin[1]);
	des_angle[3 * legNo - 1] = -1 * 180 * theta_3 / PI;

	float pos_2[2];
	pos_2[0] = pos_origin[2] - z_1_2;
	pos_2[1] = pow(pos_origin[0], 2) + pow(pos_origin[1], 2);
	pos_2[1] = pow(pos_2[1], (float) 0.5) - y_1_2; // relative to co-ordinates of the elbow joint

	float H = pow(pos_2[0], 2) + pow(pos_2[1], 2);
	H = pow(H, (float) 0.5);

	float alpha = PI / 2;
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
	theta_2 = (PI / 2) - theta_2;

	des_angle[3 * legNo - 3] = 180 * theta_1 / PI;
	des_angle[3 * legNo - 2] = 180 * theta_2 / PI;

	// directions gets reversed for the right side of the robot
	if(legNo > 3){
		des_angle[3 * legNo - 1] = -1 * des_angle[3 * legNo - 1];
		des_angle[3 * legNo - 2] = -1 * des_angle[3 * legNo - 2];
		des_angle[3 * legNo - 3] = -1 * des_angle[3 * legNo - 3];
	} // if statement end
} // function end


bool DOF_Limits(){
	int i;
	for(i = 0; i < 18; i++){
		float pwmValue = map((dir_rot[i] * angle[i] + home_value[i]), 0, 180, SERVOMIN, SERVOMAX);
		// check for joints being within limits
		if((pwmValue > SERVOMAX) || (pwmValue < SERVOMIN)){
			printf("Joint No. %i is beyond th DOF limit.\n", i+1);
			return false;
		} // if statement end
	} // for loop end
	return true;
} // function end

int map (int var, int fromMin, int fromMax, int toMin, int toMax){

	int value = 0;
	int toDiff = 0, fromDiff = 0;
	toDiff = toMax - toMin;
	fromDiff = fromMax - fromMin;
	value = (var * ((float)toDiff / (float)fromDiff));
	return (toMin + value);
}

void walkFwd(int numOfSteps){

	printf("The Hexapod will walk %i steps\n", numOfSteps);

	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	int i;
	for(i = 0; i < 18; i++)
		stepFwd1[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_fwd(true, (walk_dir * WALK_DISTANCE / 2));
	for(i = 0; i < 18; i++)
		stepFwd2[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(i = 0; i < 18; i++)
		stepFwd3[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_fwd(false, (walk_dir * WALK_DISTANCE));
	for(i = 0; i < 18; i++)
		stepFwd4[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepFwd1);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepFwd2);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepFwd3);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepFwd4);
		moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand();			// return to home position
	moveToDOFValue();
	printf("Done");
}

void walkSide(int numOfSteps){
	printf("The Hexapod will walk %i steps to the side\n", numOfSteps);

	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	int i;
	for(i = 0; i < 18; i++)
		stepSide1[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_side(true, (walk_dir * WALK_DISTANCE / 2));
	for(i = 0; i < 18; i++)
		stepSide2[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(i = 0; i < 18; i++)
		stepSide3[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_side(false, (walk_dir * WALK_DISTANCE));
	for(i = 0; i < 18; i++)
		stepSide4[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepSide1);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepSide2);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepSide3);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepSide4);
		moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand();			// return to home position
	moveToDOFValue();
	printf("Done\n");
}

void turn(int numOfSteps){
	printf("The Hexapod will turn %i steps\n", numOfSteps);

	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	int i;
	for(i = 0; i < 18; i++)
		stepTurn1[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_turn(true, (walk_dir * 10));
	for(i = 0; i < 18; i++)
		stepTurn2[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(i = 0; i < 18; i++)
		stepTurn3[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_turn(false, (walk_dir * 10));
	for(i = 0; i < 18; i++)
		stepTurn4[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepTurn1);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepTurn2);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepTurn3);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepTurn4);
		moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand();			// return to home position
	moveToDOFValue();
	printf("Done\n");
}

void walkCombined(float angle, int numOfSteps){
	printf("The Hexapod will walk %i steps diagonally\n", numOfSteps);

	int walk_dir = 1;
	if(numOfSteps < 0){
		walk_dir = -1;
		numOfSteps = -1 * numOfSteps;
	}

	leg_up(true, LEG_UP_HEIGHT);
	int i;
	for(i = 0; i < 18; i++)
		stepComb1[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_comb(true, (walk_dir * WALK_DISTANCE / 2), angle);
	for(i = 0; i < 18; i++)
		stepComb2[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_up(false, LEG_UP_HEIGHT);
	for(i = 0; i < 18; i++)
		stepComb3[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	leg_comb(false, (walk_dir * WALK_DISTANCE), angle);
	for(i = 0; i < 18; i++)
		stepComb4[i] = des_angle[i];
	moveToDOFValue();
	usleep(DELAY1 * 1000);

	for(i = 0; i < numOfSteps - 1; i++){

		setDOFValues(stepComb1);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepComb2);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepComb3);
		moveToDOFValue();
		usleep(DELAY1 * 1000);

		setDOFValues(stepComb4);
		moveToDOFValue();
		usleep(DELAY1 * 1000);
	}
	init_stand();			// return to home position
	moveToDOFValue();
	printf("Done\n");
}


void leg_up(bool left_leg, float height){
	int i;
	if(left_leg){
		for(i = 0; i < 3; i++){
		  currentPos[2 * i][2] += height; 		// increment the current position of the end effector in z-axis
		  get_DOF(currentPos[2 * i], 2 * i + 1);
		} // for loop end
	} // if statement end
	else{
		for(i = 0; i < 3; i++){
			currentPos[2 * i + 1][2] += height;
		get_DOF(currentPos[2 * i + 1], 2 * i + 2);
		} // for loop end
	}// else statement end
} // function end

void leg_fwd(bool flag, float walkDistance){
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
		int legNo = 0;
		for(legNo = 0; legNo < 6; legNo++){
			if(legNo == 0 || legNo == 2 || legNo == 3 || legNo == 5){
				currentPos[legNo][0] -= walkDistance * cos(alpha[legNo] * PI / 180);
				currentPos[legNo][1] += walkDistance * sin(alpha[legNo] * PI / 180);
			} // if statement end
			else{
				currentPos[legNo][0] += walkDistance * cos(alpha[legNo] * PI / 180);
				currentPos[legNo][1] -= walkDistance * sin(alpha[legNo] * PI / 180);
			} // else statement end
			if(legNo % 2 == 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;
			get_DOF(currentPos[legNo], legNo + 1);
		} // for loop end
	} // if statement end
	else{
		int legNo = 0;
		for(legNo = 0; legNo < 6; legNo++){
			if(legNo == 0 || legNo == 2 || legNo == 3 || legNo == 5){
				currentPos[legNo][0] += walkDistance * cos(alpha[legNo] * PI / 180);
				currentPos[legNo][1] -= walkDistance * sin(alpha[legNo] * PI / 180);
			} // if statement end
			else{
				currentPos[legNo][0] -= walkDistance * cos(alpha[legNo] * PI / 180);
				currentPos[legNo][1] += walkDistance * sin(alpha[legNo] * PI / 180);
			} // else statement end
			if(legNo % 2 != 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;
			get_DOF(currentPos[legNo], legNo + 1);
		} // for loop end
	} // else statement end
} // function end

void leg_side(bool flag, float walkDistance){
  if(flag){
	int legNo = 0;
    for(legNo = 0; legNo < 6; legNo++){
      if(legNo % 2 == 0){
        currentPos[legNo][0] += walkDistance * sin(alpha[legNo] * PI / 180);
        currentPos[legNo][1] += walkDistance * cos(alpha[legNo] * PI / 180);
        currentPos[legNo][2] -= LEG_UP_HEIGHT;
      }
      else{
        currentPos[legNo][0] -= walkDistance * sin(alpha[legNo] * PI / 180);
        currentPos[legNo][1] -= walkDistance * cos(alpha[legNo] * PI / 180);
      }
      get_DOF(currentPos[legNo], legNo + 1);
    }
  }
  else{
	int legNo = 0;
    for(legNo = 0; legNo < 6; legNo++){
      if(legNo % 2 == 0){
        currentPos[legNo][0] -= walkDistance * sin(alpha[legNo] * PI / 180);
        currentPos[legNo][1] -= walkDistance * cos(alpha[legNo] * PI / 180);
        get_DOF(currentPos[legNo], legNo + 1);
      }
      else{
        currentPos[legNo][0] += walkDistance * sin(alpha[legNo] * PI / 180);
        currentPos[legNo][1] += walkDistance * cos(alpha[legNo] * PI / 180);
        currentPos[legNo][2] -= LEG_UP_HEIGHT;
        get_DOF(currentPos[legNo], legNo + 1);
      }
    }
  }
}

void leg_turn(bool flag, float turnAngle){
	if(flag){
		int legNo = 0;
		for(legNo = 0; legNo < 6; legNo++){
			float theta_current = atan(currentPos[legNo][1] / currentPos[legNo][0]);
			float radius = pow(currentPos[legNo][0], 2) + pow(currentPos[legNo][1], 2);
			radius = pow(radius, (float)0.5);
			float theta_final = 0;

			if(legNo == 0 || legNo == 2 || legNo == 3 || legNo == 5){
				theta_final = theta_current + (turnAngle * PI / 180);
			}
			else{
				theta_final = theta_current - (turnAngle * PI / 180);
			}

			if(legNo % 2 == 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;

			currentPos[legNo][0] = radius * cos(theta_final);
			currentPos[legNo][1] = radius * sin(theta_final);
			get_DOF(currentPos[legNo], legNo + 1);
		}
	}
	else{
		int legNo = 0;
		for(legNo = 0; legNo < 6; legNo++){
			float theta_current = atan(currentPos[legNo][1] / currentPos[legNo][0]);
			float radius = pow(currentPos[legNo][0], 2) + pow(currentPos[legNo][1], 2);
			radius = pow(radius, (float)0.5);
			float theta_final = 0;

			if(legNo == 1 || legNo == 4){
				theta_final = theta_current + (turnAngle * PI / 180);
			}
			else{
				theta_final = theta_current - (turnAngle * PI / 180);
			}

			if(legNo % 2 != 0)
				currentPos[legNo][2] -= LEG_UP_HEIGHT;

			currentPos[legNo][0] = radius * cos(theta_final);
			currentPos[legNo][1] = radius * sin(theta_final);
			get_DOF(currentPos[legNo], legNo + 1);
		}
	}
}

void leg_comb(bool flag, float walkDistance, float angle){
	angle = PI * angle / 180;
	leg_fwd(flag, (walkDistance * cos(angle)));
	leg_up(flag, LEG_UP_HEIGHT);
	leg_side(flag, (walkDistance * sin(angle)));
}

void reliefStep(){
	bool left_leg = true;

	// to reduce drag the legs have to do a relief procedure
	int i;
	for(i = 0; i < 2; i++){
		leg_up(left_leg, LEG_UP_HEIGHT);
		moveToDOFValue();
		leg_up(left_leg, -LEG_UP_HEIGHT);
		moveToDOFValue();
		left_leg = false;
	}
}

