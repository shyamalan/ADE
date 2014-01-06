CC = gcc

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
