
CC = g++

default: sensor2
	@echo Executable located in bin

sensor2: master.o Sensor.o Serial.o
	$(CC) master.o Sensor.o Serial.o -o ../bin/sensor

face.o: ../src/face.cpp
	$(CC) -c ../src/face.cpp

sensor1: Sensor.o Serial.o master.o i2c-common.o MMA7455.o
	$(CC) Sensor.o Serial.o master.o i2c-common.o MMA7455.o -o ../bin/sensor

Sensor.o: ../src/Sensor.cpp
	$(CC) -c ../src/Sensor.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

MMA7455.o: ../src/MMA7455.cpp
	$(CC) -c ../src/MMA7455.cpp

send: message_send.o rangeFinder.o SlaveDevice.o
	$(CC) message_send.o rangeFinder.o SlaveDevice.o -o ../bin/message_send

receive: ../src/message_rec.cpp
	$(CC) ../src/message_rec.cpp -o ../bin/message_rec

message_send.o: ../src/message_send.cpp
	$(CC) -c ../src/message_send.cpp

all: angstrom_avoid_obj key_input
	@echo Execulable located in bin

sample: sample_pub sample_sub

sample_pub: sample_pub.o master.o pubsub.o Serial.o SRF08.o SlaveDevice.o
	$(CC) sample_pub.o master.o pubsub.o Serial.o SRF08.o SlaveDevice.o -o ../bin/sample_pub

sample_sub: sample_sub.o master.o pubsub.o Serial.o
	$(CC) sample_sub.o master.o pubsub.o Serial.o -o ../bin/sample_sub

sample_sub.o: ../src/sample_sub.cpp
	$(CC) -c ../src/sample_sub.cpp

sample_pub.o: ../src/sample_pub.cpp
	$(CC) -c ../src/sample_pub.cpp

SRF08.o: ../src/SRF08.cpp
	$(CC) -c ../src/SRF08.cpp
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

angstrom_avoid_obj: angstrom_avoid_obj.o pubsub.o Serial.o master.o SlaveDevice.o Hexapod.o AdaFruitServoDriver.o 
	$(CC) angstrom_avoid_obj.o master.o pubsub.o Serial.o SlaveDevice.o Hexapod.o AdaFruitServoDriver.o -o ../bin/angstrom_avoid_obj

key_input: key_input.o master.o Serial.o pubsub.o
	$(CC) key_input.o pubsub.o master.o Serial.o -o ../bin/key_input

key_input.o: ../src/key_input.cpp
	$(CC) -c ../src/key_input.cpp

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

i2c-common.o: ../src/i2c-common.cpp
	$(CC) -c ../src/i2c-common.cpp

clean:
	$(RM) *.o *~ ../bin/*
