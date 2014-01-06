
CC = g++

default: send receive  
	@echo Executable located in bin

send: message_send.o rangeFinder.o SlaveDevice.o
	$(CC) message_send.o rangeFinder.o SlaveDevice.o -o ../bin/message_send

receive: ../src/message_rec.cpp
	$(CC) ../src/message_rec.cpp -o ../bin/message_rec

message_send.o: ../src/message_send.cpp
	$(CC) -c ../src/message_send.cpp

all: angstrom_avoid_obj
	@echo Execulable located in bin

sample: sample_pub sample_sub

sample_pub: sample_pub.o master.o rangeFinder.o SlaveDevice.o pubsub.o Serial.o
	$(CC) sample_pub.o master.o rangeFinder.o SlaveDevice.o pubsub.o Serial.o -o ../bin/sample_pub

sample_sub: sample_sub.o master.o pubsub.o Serial.o
	$(CC) sample_sub.o master.o pubsub.o Serial.o -o ../bin/sample_sub

sample_sub.o: ../src/sample_sub.cpp
	$(CC) -c ../src/sample_sub.cpp

sample_pub.o: ../src/sample_pub.cpp
	$(CC) -c ../src/sample_pub.cpp

master.o: ../src/master.cpp
	$(CC) -c ../src/master.cpp

pubsub.o: ../src/pubsub.cpp
	$(CC) -c ../src/pubsub.cpp

Serial.o: ../src/Serial.cpp
	$(CC) -c ../src/Serial.cpp

facedetect: faceDetect.o
	$(CC) faceDetect.o -o ../bin/faceDetect -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

faceDetect.o: ../src/faceDetect.cpp
	$(CC) -c ../src/faceDetect.cpp

angstrom_avoid_obj: Serial.o angstrom_avoid_obj.o SlaveDevice.o Hexapod.o AdaFruitServoDriver.o 
	$(CC) angstrom_avoid_obj.o Serial.o SlaveDevice.o Hexapod.o AdaFruitServoDriver.o -o ../bin/angstrom_avoid_obj

rangeFinder.o: ../src/rangeFinder.cpp
	$(CC) -c ../src/rangeFinder.cpp

angstrom_avoid_obj.o: ../src/angstrom_avoid_obj.cpp
	$(CC) -c ../src/angstrom_avoid_obj.cpp

arm.o: ../src/arm.cpp
	$(CC) -c ../src/arm.cpp

Hexapod.o: ../src/Hexapod.cpp ../src/Hexapod.h
	$(CC) -c ../src/Hexapod.cpp

AdaFruitServoDriver.o: ../src/AdaFruitServoDriver.cpp ../src/AdaFruitServoDriver.h
	$(CC) -c ../src/AdaFruitServoDriver.cpp

Matrix.o: ../src/Matrix.cpp ../src/Matrix.h
	$(CC) -c ../src/Matrix.cpp

SlaveDevice.o: ../src/SlaveDevice.cpp ../src/SlaveDevice.h
	$(CC) -c ../src/SlaveDevice.cpp

clean:
	$(RM) *.o *~ ../bin/*
