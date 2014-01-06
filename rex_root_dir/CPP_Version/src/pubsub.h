#ifndef PUBSUB_H_
#define PUBSUB_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MSGSZ 128

class message_buf{
public:
	long mtype;
	char mtext[MSGSZ];
};

bool publish(key_t, char*, int);

bool subscribe(key_t, char*, int);

bool endTransfer(key_t);

#endif
