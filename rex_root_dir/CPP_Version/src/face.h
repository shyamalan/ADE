
#ifndef FACE_H_
#define FACE_H_

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


String face_cascade_name = "../haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
RNG rng(12345);
CvCapture* capture;
Mat frame;
std::vector<Rect> faces;

int detect ();

float* face_pos();

#endif


