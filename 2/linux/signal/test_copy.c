#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>

// WARNING! GLOBAL VARIABLES!!!!!!!!!!!!!!!!!
int semId = 0;
unsigned char currByte = 1;
int recievedBytes = 0;


int AnalyseKeys (int argc, char** argv);

void IncSem ();
void DecSem ();

void SendByte (unsigned char byte, int pid);
void RecieveByte ();

void SignalHandler1 ();
void SignalHandler2 ();




int AnalyseKeys (int argc, char** argv)
{
	assert (argc > 1);
	assert (argv);
	assert (argv[1]);

	if (argc == 2)
	{
		if (!strcmp (argv[1], "-r") || !strcmp (argv[1], "--recieve"))
		{
			return 0;
		}
	}
	else
	{
		if ((!strcmp (argv[1], "-s") || !strcmp (argv[1], "--send")) && argc == 4)
		{
			int pid = 0;
			sscanf (argv[2], "%d", &pid);
			return pid;
		}
	}

	return -1;
}


void IncSem ()
{
	assert (semId >= 0);

	struct sembuf myBuf = {};
	myBuf.sem_num = 0;
	myBuf.sem_op = 1;
	myBuf.sem_flg = 0;
	semop (semId, &myBuf, 1);
}

void DecSem ()
{
	assert (semId >= 0);

	struct sembuf myBuf = {};
	myBuf.sem_num = 0;
	myBuf.sem_op = -1;
	myBuf.sem_flg = 0;
	semop (semId, &myBuf, 1);
}



void SendByte (unsigned char byte, int pid)
{
	assert (semId >= 0);
	assert (byte >= 0);
	assert (pid > 0);

	int i = 0;
//	int j = 0;
	for (i = 7; i >= 0; i--)
	{
		DecSem (semId);

		if ((byte >> i) % 2)
		{
			kill (pid, SIGUSR1);
		}
		else
		{
			kill (pid, SIGUSR2);
		}

//		for (j = 0; j < 1000000; j++);
	}
}


void RecieveByte ()
{
	int i = 0;
	IncSem ();

	while (i < 8)
	{
		if (i != recievedBytes)
		{
			i++;
			if (i < 8)
			{
				IncSem ();
			}
		}
	}

	recievedBytes = 0;
}


void SignalHandler1 ()
{
	currByte = currByte * 2 + 1;
	recievedBytes++;
}

void SignalHandler2 ()
{
	currByte = currByte * 2;
	recievedBytes++;
}



int main (int argc, char** argv, char** env)
{
	printf ("myPID = %d\n", getpid ());
	int pid = AnalyseKeys (argc, argv);
	/*if (pid < 0)
	{
		printf ("ERROR. Problems with keys.\n");
		return 0;
	}*/

	int key = ftok ("keyfile", 0);
	assert (key >= 0);
	semId = semget (key, 1, IPC_CREAT | 0666);
	assert (semId >= 0);

	if (!pid)
	{
		signal (SIGUSR1, SignalHandler1);
		signal (SIGUSR2, SignalHandler2);

		while (currByte)
		{
			currByte = 0;
			RecieveByte ();
			printf ("%c\n", currByte, currByte);
		}

		semctl (semId, 0, IPC_RMID, 0);
	}
	else
	{
		assert (argv[3]);
		int lenStr = strlen (argv[3]);
		int i = 0;

		for (i = 0; i <= lenStr; i++)
		{
			SendByte (*(argv[3] + i), pid);
		}
	}

	return 0;
}






















