#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define MSG_LEN 1024
#define QUEUE_SIZE 10
#define USR_NAME_SIZE 20
#define PORT_NUM 50000


struct ClientInfo
{
	int* clientCount;
	int* allSockets;
	int socketDesc;
	int semId;
};




void IncSem (int semId)
{
	assert (semId >= 0);

	struct sembuf myBuf = {};
	myBuf.sem_num = 0;
	myBuf.sem_op = 1;
	myBuf.sem_flg = 0;
	semop (semId, &myBuf, 1);
}

void DecSem (int semId)
{
	assert (semId >= 0);

	struct sembuf myBuf = {};
	myBuf.sem_num = 0;
	myBuf.sem_op = -1;
	myBuf.sem_flg = 0;
	semop (semId, &myBuf, 1);
}



int AddNewSocket (int* allSockets, int* clientCount, int newSocket)
{
	assert (allSockets);
	assert (clientCount);
	assert (newSocket >= 0);

	int i = 0;
	for (i = 0; i < QUEUE_SIZE; i++)
	{
		if (allSockets[i] == -1)
		{
			allSockets[i] = newSocket;
			return 0;
		}
	}

	return -1;
}


int RemoveSocket (int* allSockets, int* clientCount, int removeSocket)
{
	assert (allSockets);
	assert (clientCount);
	assert (removeSocket >= 0);

	int i = 0;
	for (i = 0; i < QUEUE_SIZE; i++)
	{
		if (allSockets[i] == removeSocket)
		{
			allSockets[i] = -1;
			return 0;
		}
	}

	return -1;
}





void* ThreadServer (void* args)
{
	assert (args);

	struct ClientInfo client = *(struct ClientInfo*) args;
	int recvRes = 0;
	char buffer[MSG_LEN] = {};
	int i = 0;

	assert (client.clientCount);
	assert (client.allSockets);
	assert (client.semId >= 0);

	printf ("New client connected. There are %d active clients.\n", *(client.clientCount));

	while (recvRes = recv (client.socketDesc, buffer, MSG_LEN, 0) > 0)
	{
		DecSem (client.semId);

		for (i = 0; i < *(client.clientCount); i++)
		{
			assert (client.allSockets + i);
			if (client.allSockets[i] != client.socketDesc)
			{
				sleep (2);
				send (client.allSockets[i], buffer, strlen (buffer) + 1, 0);
			}
		}

		IncSem (client.semId);
	}

	DecSem (client.semId);
	(*(client.clientCount))--;
	if (RemoveSocket (client.allSockets, client.clientCount, client.socketDesc) < 0)
	{
		printf ("WARNING. Wrong returning value of the function 'RemoveSocket'.\n");
	}
	IncSem (client.semId);

	printf ("Client disconnected. There are %d active clients.\n", *(client.clientCount));
	assert (!recvRes);
}





void WorkServer ()
{
	int passSocketDesc = socket (AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in myAddress = {};
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons (PORT_NUM);
	inet_aton ("127.0.0.1", &(myAddress.sin_addr));
	bind (passSocketDesc, (struct sockaddr*) &myAddress, sizeof (myAddress));

	listen (passSocketDesc, QUEUE_SIZE);
	struct ClientInfo newClient = {};
	int clientCount = 0;
	int newSocket = 0;
	int allSockets[QUEUE_SIZE] = {};
	int semId = semget (IPC_PRIVATE, 1, 0666);
	IncSem (semId);
	newClient.allSockets = allSockets;
	newClient.semId = semId;
	pthread_t newThreadId = 0;

	int i = 0;
	for (i = 0; i < QUEUE_SIZE; i++)
	{
		allSockets[i] = -1;
	}

	while (1)
	{
		assert (0 <= clientCount && clientCount < QUEUE_SIZE);
		newSocket = accept (passSocketDesc, 0, 0);

		if (clientCount >= QUEUE_SIZE)
		{
			printf ("Too many clients. Connsection hasn't set.\n");
		}
		else
		{
			if (AddNewSocket (allSockets, &clientCount, newSocket) < 0)
			{
				printf ("WARNING. Wrong returning value of the function 'AddNewSocket'.\n");
			}
			clientCount++;

			newClient.clientCount = &clientCount;
			newClient.socketDesc = newSocket;

			pthread_create (&newThreadId, 0, ThreadServer, &newClient);
		}
	}
}




void* ThreadClient (void* args)
{
	assert (args);

	int socketDesc = *(int*) args;
	char buffer[MSG_LEN] = {};
	int recvRes = 0;

	while (1)
	{
		recvRes = recv (socketDesc, buffer, MSG_LEN, 0);
		if (recvRes <= 0)
		{
			printf ("Server has shut down. Connection has been lost. recvRes = %d\n", recvRes);
			exit (0);
		}
		printf ("%s\n", buffer);
	}
}



void WorkClient ()
{
	printf ("Enter your name: ");
	char buffer[MSG_LEN] = {};
	scanf ("%s", buffer);
	strcat (buffer, ": ");
	int nameLen = strlen (buffer);

	int socketDesc = socket (AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress = {};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons (PORT_NUM);
	inet_aton ("127.0.0.1", &(serverAddress.sin_addr));
	connect (socketDesc, (struct sockaddr*) &serverAddress, sizeof (serverAddress));

	pthread_t newThreadId = 0;
	pthread_create (&newThreadId, 0, ThreadClient, &socketDesc);

	while (1)
	{
		scanf ("%s", buffer + nameLen);
		buffer[strlen (buffer)] = 0;
		send (socketDesc, buffer, strlen (buffer) + 1, 0);
	}
}








int main (int argc, char** argv)
{
	assert (argc == 2);

	if (!strcmp (argv[1], "-s") || !strcmp (argv[1], "--server"))
	{
		WorkServer ();
	}
	else
	{
		WorkClient ();
	}

	return 0;
}




















