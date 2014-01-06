#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <iostream>

#define MSGSZ     128
using namespace std;

/*
 * Declare the message structure.
 */

class message_buf {
public:
    long    mtype;
    char    mtext[MSGSZ];
};


int main()
{
    int msqid;
    key_t key;
    message_buf  rbuf;

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 1234;

    if ((msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666)) < 0) {
        perror("msgget");
//        return 1;
    }

    cout << msqid << endl;    
    /*
     * Receive an answer of message type 1.
     */
    for(int i = 0; i < 5; i++){
    	if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        	perror("msgrcv");
       		return 1;
    	}
//        printf("%i\n", rbuf.mtext[0]);
	cout << (int)rbuf.mtext[0] << endl;
    }
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}
