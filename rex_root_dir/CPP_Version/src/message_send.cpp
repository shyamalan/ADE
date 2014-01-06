#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MSGSZ     128
using namespace std;

/*
 * Declare the message structure.
 */

class message_buf {
public:
         long mtype;
         char mtext[MSGSZ];
         };

int main()
{	
    int msqid;
    int msgflg = IPC_CREAT|IPC_EXCL|0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 1234;

    if ((msqid = msgget(key, msgflg)) < 0) {
        msqid = msgget(key,0666);
//        return 1;
   }
   cout << msqid << endl;
   sbuf.mtype = 1;
   
   buf_length = 1;
   sbuf.mtext[0] = (char)10;
   for(int i = 0; i < 5; i++){
   	if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
   		printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
	       	perror("msgsnd");
       		return 1;
	}
   }
//   msgctl(msqid, IPC_RMID, NULL);

   return 0;
}
