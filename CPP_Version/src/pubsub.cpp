#include "pubsub.h"


/*
 * Declare the message structure.
 */

int message_send()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	size_t buf_length;

	/*
	* Get the message queue id for the
	* "name" 1234, which was created by
	* the server.
	*/
	key = 1234;

	(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,%#o)\n",key, msgflg);

	if ((msqid = msgget(key, msgflg )) < 0) {
		perror("msgget");
		return 1;
	}
	else 
		(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);


	/*
	* We'll send message type 1
	*/
     
	sbuf.mtype = 1;

	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);

	(void) strcpy(sbuf.mtext, "Did you get this?");

	(void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);

	buf_length = strlen(sbuf.mtext) + 1 ;



	/*
	* Send a message.
	*/
	if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
		printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
		perror("msgsnd");
		return 1;
	}

	else 
		printf("Message: \"%s\" Sent\n", sbuf.mtext);

	return 0;
}

int message_rec(){
	int msqid;
	key_t key;
	message_buf  rbuf;

	/*
	* Get the message queue id for the
	* "name" 1234, which was created by
	* the server.
	*/
	key = 1234;

	if ((msqid = msgget(key, 0666)) < 0) {
		perror("msgget");
		return 1;
	}

    
	/*
	* Receive an answer of message type 1.
	*/
	if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
		perror("msgrcv");
		return 1;
	}

	/*
	* Print the answer.
	*/
	printf("%s\n", rbuf.mtext);
	return 1;
}
