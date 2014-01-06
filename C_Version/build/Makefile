
CFLAGS = -I/opt/alphalem/0.1.0/sysroots/armv5te-poky-linux-gnueabi/usr/include/c++ -L/opt/alphalem/0.1.0/sysroots/armv5te-poky-linux-gnueabi/usr/lib -g3 -Wall

PATH := /opt/alphalem/0.1.0/sysroots/x86_64-pokysdk-linux/usr/bin:/opt/alphalem/0.1.0/sysroots/x86_64-pokysdk-linux/usr/bin/armv5te-poky-linux-gnueabi:$(PATH)

CC = gcc
CROSS_CC = arm-poky-linux-gnueabi-gcc
CV_CFLAGS = -I/usr/local/include/opencv -I/usr/local/include/opencv2

CV_LIBS = /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_superres.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so 

default: send receive
	@echo Executable located in bin

send: ../src/message_send.c
	$(CC) ../src/message_send.c -o ../bin/message_send

receive: ../src/message_rec.c
	$(CC) ../src/message_rec.c -o ../bin/message_rec

toby: toby.o hexapod.o adaFruitDriver.o slaveDevice.o
	$(CC) toby.o hexapod.o adaFruitDriver.o slaveDevice.o -o ../bin/toby -lm

toby.o: ../src/toby.c
	$(CC) -c ../src/toby.c

arm.o: ../src/arm.c
	$(CC) $(CFLAGS) -c ../src/arm.c ../src/arm.h

hexapod.o: ../src/hexapod.c ../src/hexapod.h
	$(CC) -c ../src/hexapod.c ../src/hexapod.h

adaFruitDriver.o: ../src/adaFruitDriver.c ../src/adaFruitDriver.h
	$(CC) -c ../src/adaFruitDriver.c ../src/adaFruitDriver.h

slaveDevice.o: ../src/slaveDevice.c ../src/slaveDevice.h
	$(CC) -c ../src/slaveDevice.c ../src/slaveDevice.h

clean:
	$(RM) *.o *~ ../bin/*
