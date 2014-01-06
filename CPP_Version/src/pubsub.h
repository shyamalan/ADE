#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MSGSZ 128

class message_buf {
public:
	long mtype;
	char mtext[MSGSZ];
};

int message_send();

int message_rec();
