#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/msg.h>
#include <unistd.h>
#include <assert.h>

#define PIECE_STRING 8


struct Message
{
	long type;
	int length;
	char str[PIECE_STRING];
};



void* ThreadMain (void* args)
{
	assert (args);

	int msqId = *(int*) args;
	int msgSize = sizeof (struct Message) - sizeof (long);
	struct Message msg = {};
	msg.type = 2;
	int readRes = 0;

	while (1)
	{
		msg.length = read (0, msg.str, PIECE_STRING);
//		printf ("2! readRes = %d\n", msg.length);
		msgsnd (msqId, &msg, msgSize, 0);
	}
}



int main ()
{
	int key = ftok ("keyfile", 0);
	int msqId = msgget (key, IPC_CREAT | 0666);

	pthread_t threadId = 0;
	pthread_create (&threadId, NULL, ThreadMain, &msqId);

	int msgSize = sizeof (struct Message) - sizeof (long);
	struct Message msg = {};
	int i = 0;

	while (1)
	{
		msgrcv (msqId, &msg, msgSize, 1, 0);
		for (i = 0; i < msg.length; i++)
		{
			printf ("%c", msg.str[i]);
		}
	}

	return 0;
}









