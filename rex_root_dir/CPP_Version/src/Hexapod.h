/*
 * Hexapod.h
 *
 *  Created on: Aug 18, 2013
 *      Author: kartik
 */

#ifndef HEXAPOD_H_
#define HEXAPOD_H_

#include "MatrixMath.h"
#include "AdaFruitServoDriver.h"
#include <iostream>
#include <math.h>

// physical constants for each leg
// same for each leg
#define x_1_2 0.0
#define y_1_2 1.0
#define z_1_2 -1.0

#define x_2_3 3.0
#define y_2_3 0.0
#define z_2_3 0.0

#define x_3_ee 1.47
#define y_3_ee 3.785
#define z_3_ee 0.0


//home positions for each servo in terms of its abs rotation angle

#define HOME_1 87
#define HOME_2 123
#define HOME_3 87
#define HOME_4 85
#define HOME_5 147
#define HOME_6 80
#define HOME_7 86
#define HOME_8 127
#define HOME_9 7
#define HOME_10 93
#define HOME_11 50
#define HOME_12 87
#define HOME_13 100
#define HOME_14 43
#define HOME_15 85
#define HOME_16 93
#define HOME_17 27
#define HOME_18 85

#define THRESHOLD 3
#define DELAY1 0 // for delay between steps
#define DELAY2 2 // for delay between increments

// increments for different actions
#define INCREMENT 3.0 		// increment for reaching a desired angle
#define WALK_DISTANCE 1.5	// step length for each step in inches
#define LEG_UP_HEIGHT 1.5	// value in inches of the height for leg up position
//#define HEIGHT -4.0
const float pi = 3.14;

class Hexapod{
private:
	AdaFruitServoDriver driver1, driver2;
	int alpha[6];	// this will contain rotation of the leg origin to abs origin
					// different for different legs
	int home_value[18];
	int angle[18];		// current angle
	int des_angle[18];	// desired angle
	int angle_inc[18];	// increment in angle for each step
	int dir_rot[18];	// direction of rotation w.r.t right hand rule

	float currentPos[6][3]; // leg tip coordinates for standing pos

	// variables to store DOF values after first step
	int stand[18];
	int stepFwd1[18];
	int stepFwd2[18];
	int stepFwd3[18];
	int stepFwd4[18];
	int stepSide1[18];
	int stepSide2[18];
	int stepSide3[18];
	int stepSide4[18];
	int stepTurn1[18];
	int stepTurn2[18];
	int stepTurn3[18];
	int stepTurn4[18];
	int stepComb1[18];
	int stepComb2[18];
	int stepComb3[18];
	int stepComb4[18];

	bool prob;
	float HEIGHT;
	void init_stand(float);
	bool moveToDOFValue();				// go to the desired angle for a particular DOF
	void setDOFValues(int[]);			// update the desired DOF values
	void get_DOF(float[], int);			// IK solution for the given set of end effector position
	bool DOF_Limits();					// DOF limit check
	void leg_up(bool, float);			// set the DOF values to leg up position (alternate legs only)
	void leg_fwd(bool, float);			// set the DOF values to leg forward position (alternate legs only)
	void leg_side(bool, float);
	void leg_comb(bool, float, float);
	void leg_turn(bool, float);
	int map(int, int, int, int, int);
public:
	void Hexapod_init();						// initialize the robot stance/position
	void stand_pos(float);
	void rise(float);
	bool walkFwd(int);
	bool walkSide(int);
	bool turn(int);
	bool walkCombined(float, int);
	bool stanceRoll(int);
	bool stancePitch(int);
	bool stanceYaw(int);
	bool reliefStep();					// relief step after each sequence of steps
	bool move_single_leg(int, float[]);
	~Hexapod();
};


#endif /* HEXAPOD_H_ */
