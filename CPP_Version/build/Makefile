
CFLAGS = -I/opt/alphalem/0.1.0/sysroots/armv5te-poky-linux-gnueabi/usr/include/c++ -L/opt/alphalem/0.1.0/sysroots/armv5te-poky-linux-gnueabi/usr/lib -g3 -Wall

PATH := /opt/alphalem/0.1.0/sysroots/x86_64-pokysdk-linux/usr/bin:/opt/alphalem/0.1.0/sysroots/x86_64-pokysdk-linux/usr/bin/armv5te-poky-linux-gnueabi:$(PATH)

CC = g++
CROSS_CC = arm-poky-linux-gnueabi-g++
CV_CFLAGS = -I/usr/local/include/opencv -I/usr/local/include/opencv2

CV_LIBS = /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_superres.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

default: send receive
	@echo Executable located in bin

send: ../src/message_send.cpp
	$(CC) ../src/message_send.cpp -o ../bin/message_send

receive: ../src/message_rec.cpp
	$(CC) ../src/message_rec.cpp -o ../bin/message_rec

all: angstrom_avoid_obj facedetect
	@echo Execulable located in bin

sample: alphalem_sample.o master.o Serial.o
	$(CC) alphalem_sample.o master.o Serial.o -o ../bin/sample

alphalem_sample.o: ../src/alphalem_sample.cpp
	$(CC) -c ../src/alphalem_sample.cpp

master.o: ../src/master.cpp
	$(CC) -c ../src/master.cpp

Serial.o: ../src/Serial.cpp
	$(CC) -c ../src/Serial.cpp

facedetect: faceDetect.o
	$(CC) $(CV_CFLAGS) $(CV_LIBS) faceDetect.o -o ../bin/faceDetect

faceDetect.o: ../src/faceDetect.cpp
	$(CC) $(CV_LIBS) -c ../src/faceDetect.cpp

angstrom_avoid_obj: angstrom_avoid_obj.o Hexapod.o AdaFruitServoDriver.o SlaveDevice.o
	$(CROSS_CC) $(CFLAGS) angstrom_avoid_obj.o Hexapod.o AdaFruitServoDriver.o SlaveDevice.o -o ../bin/angstrom_avoid_obj

angstrom_avoid_obj.o: ../src/angstrom_avoid_obj.cpp
	$(CROSS_CC) $(CFLAGS) -c ../src/angstrom_avoid_obj.cpp

arm.o: ../src/arm.cpp
	$(CROSS_CC) $(CFLAGS) -c ../src/arm.cpp

Hexapod.o: ../src/Hexapod.cpp ../src/Hexapod.h
	$(CROSS_CC) $(CFLAGS) -c ../src/Hexapod.cpp

AdaFruitServoDriver.o: ../src/AdaFruitServoDriver.cpp ../src/AdaFruitServoDriver.h
	$(CROSS_CC) $(CFLAGS) -c ../src/AdaFruitServoDriver.cpp

Matrix.o: ../src/Matrix.cpp ../src/Matrix.h
	$(CROSS_CC) $(CFLAGS) -c ../src/Matrix.cpp

SlaveDevice.o: ../src/SlaveDevice.cpp ../src/SlaveDevice.h
	$(CROSS_CC) $(CFLAGS) -c ../src/SlaveDevice.cpp

clean:
	$(RM) *.o *~ ../bin/*
