/*
 * MatrixMath.h
 *
 *  Created on: Aug 16, 2013
 *      Author: kartik
 */

#ifndef MatrixMath_h
#define MatrixMath_h
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class MatrixMath
{
public:
	//MatrixMath();
	void Print(float* A, int m, int n, string label);
	void Copy(float* A, int n, int m, float* B);
	void Multiply(float* A, float* B, int m, int p, int n, float* C);
	void Add(float* A, float* B, int m, int n, float* C);
	void Subtract(float* A, float* B, int m, int n, float* C);
	void Transpose(float* A, int m, int n, float* C);
	void Scale(float* A, int m, int n, float k);
	int Invert(float* A, int n);
};

extern MatrixMath Matrix;
#endif
