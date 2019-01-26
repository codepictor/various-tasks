#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <assert.h>


enum Error_t
{
	ERR_HAPPINESS  = 0,
	ERR_WRONG_KEY  = 1,
	ERR_WRONG_ARGS = 2,
	ERR_KEYFILE    = 3,
	ERR_OTHER      = 4

};


enum KeyType_t
{
	KEYTYPE_HELP  = 0,
	KEYTYPE_FILE  = 1,
	KEYTYPE_RESET = 2,
	KEYTYPE_PRINT = 3,
	KEYTYPE_CALC  = 4,
	KEYTYPE_ERROR = 5
};


struct Key
{
	int type;
	int argc;
	char** args;
};


void IncSem (int semId);
void DecSem (int semId);

void PrintDiagnostic (const int errNum);
void PrintHelp       ();

int GetKeyCount   (const int argc, char** const args);
int FillStructKey (const int keyCount, struct Key* ptrKeys, char** const args);

int GetKey   (const int keyCount, struct Key* const ptrKeys);
int GetSemId (const int key, const int keyCount);
int GetShmId (const int key, const int keyCount);

void Calculating (long long int* data, const int semId);

void CheckHelpKey      (const int keyCount, struct Key* const ptrKeys);
void CheckPrintKey     (const int keyCount, struct Key* const ptrKeys, long long int* data);
void CheckResetKey     (const int keyCount, struct Key* const ptrKeys, const int semId, const int shmId);
void CheckCalculateKey (const int keyCount, struct Key* ptrKeys, long long int* data, const int semId);




int main (int argc, char** args, char** env)
{
	const int keyCount = GetKeyCount (argc, args);
	if (keyCount < 0)
	{
		PrintDiagnostic (ERR_WRONG_KEY);
		return 0;
	}

	struct Key* ptrKeys = (struct Key*) calloc (keyCount, sizeof (struct Key));
	assert (ptrKeys);
	if (FillStructKey (keyCount, ptrKeys, args))
	{
		PrintDiagnostic (ERR_WRONG_ARGS);
		return 0;
	}

	const int key = GetKey (keyCount, ptrKeys);
	if (key < 0)
	{
		PrintDiagnostic (ERR_KEYFILE);
		return 0;
	}

	int semId = GetSemId (key, keyCount);
	assert (semId >= 0);
	int shmId = GetShmId (key, keyCount);
	assert (shmId >= 0);
	long long int* data = (long long int*) shmat (shmId, NULL, 0);
	assert (data);

	CheckCalculateKey (keyCount, ptrKeys, data, semId);
	CheckHelpKey (keyCount, ptrKeys);
	CheckPrintKey (keyCount, ptrKeys, data);
	shmdt ((char*) data);
	CheckResetKey (keyCount, ptrKeys, semId, shmId);

	free (ptrKeys);
	ptrKeys = NULL;

	return 0;
}




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



void PrintDiagnostic (const int errNum)
{
	assert (0 <= errNum && errNum < ERR_OTHER);

	switch (errNum)
	{
		case ERR_HAPPINESS:  printf ("Everything is all right. Who called the function 'PrintDiagnostic'?\n"); break;
		case ERR_WRONG_KEY:  printf ("ERROR. Wrong key of command line.\n");                                   break;
		case ERR_WRONG_ARGS: printf ("ERROR. Incorrect arguments of keys.\n");                                 break;
		case ERR_KEYFILE:    printf ("ERROR. Can't create key. Problems with a key file.\n");                  break;
		default:             printf ("ERROR. But I don't know anything about this error.\n");
	}
}

void PrintHelp ()
{
	printf ("-h --help\n   Printing manual\n");
	printf ("-c --calculate\n   Run calculations\n");
	printf ("-k --keyfile {keyfile}\n   Choose file for creating key\n");
	printf ("-r --reset\n   Remove semaphore and shared memory\n");
	printf ("-p --print\n   Printing current results\n");
}



int GetKeyCount (const int argc, char** const args)
{
	assert (argc > 0);
	assert (args);
	assert (args[argc - 1]);

	int keyCount = 0;
	int prevKeyCount = 0;
	int i = 0;
	for (i = 1; i < argc; i++)
	{
		prevKeyCount = keyCount;

		if (!strcmp (args[i], "--help") || !strcmp (args[i], "--keyfile") || !strcmp (args[i], "--reset") || !strcmp (args[i], "--print") || !strcmp (args[i], "--calculate"))
		{
			keyCount++;
		}
		
		if (!strcmp (args[i], "-h") || !strcmp (args[i], "-k") || !strcmp (args[i], "-r") || !strcmp (args[i], "-p") || !strcmp (args[i], "-c"))
		{
			keyCount++;
		}

		if (!strcmp (args[i], "--keyfile") || !strcmp (args[i], "-k"))
		{
			i++;
		}

		if (prevKeyCount == keyCount)
		{
			return -1;
		}
	}

	return keyCount;
}


int FillStructKey (const int keyCount, struct Key* ptrKeys, char** const args)
{
	assert (keyCount >= 0);
	assert (ptrKeys);
	assert (args);

	int i = 0;
	int j = 1;
	for (i = 0; i < keyCount; i++)
	{
		(ptrKeys + i)->type = KEYTYPE_ERROR;

		if (!strcmp (args[j], "-h") || !strcmp (args[j], "--help"))
		{	
			(ptrKeys + i)->type = KEYTYPE_HELP;
			(ptrKeys + i)->argc = 0;
			(ptrKeys + i)->args = NULL;
		}
		if (!strcmp (args[j], "-k") || !strcmp (args[j], "--keyfile"))
		{	
			(ptrKeys + i)->type = KEYTYPE_FILE;
			(ptrKeys + i)->argc = 1;
			j = j + 1;
			(ptrKeys + i)->args = (char**) calloc (1, sizeof (char*));
			((ptrKeys + i)->args)[0] = args[j];
		}
		if (!strcmp (args[j], "-r") || !strcmp (args[j], "--reset"))
		{	
			(ptrKeys + i)->type = KEYTYPE_RESET;
			(ptrKeys + i)->argc = 0;
			(ptrKeys + i)->args = NULL;
		}
		if (!strcmp (args[j], "-p") || !strcmp (args[j], "--print"))
		{	
			(ptrKeys + i)->type = KEYTYPE_PRINT;
			(ptrKeys + i)->argc = 0;
			(ptrKeys + i)->args = NULL;
		}
		if (!strcmp (args[j], "-c") || !strcmp (args[j], "--calculate"))
		{
			(ptrKeys + i)->type = KEYTYPE_CALC;
			(ptrKeys + i)->argc = 0;
			(ptrKeys + i)->args = NULL;
		}

		if ((ptrKeys + i)->type == KEYTYPE_ERROR)
		{
			return -1;
		}

		j++;
	}

	return 0;
}



int GetKey (const int keyCount, struct Key* const ptrKeys)
{
	assert (keyCount >= 0);
	assert (ptrKeys);

	int i = 0;
	int key = 0;
	int keyFlag = 0;
	for (i = 0; i < keyCount; i++)
	{
		assert (0 <= (ptrKeys + i)->type && (ptrKeys + i)->type < KEYTYPE_ERROR);
		if ((ptrKeys + i)->type == KEYTYPE_FILE && !keyFlag)
		{
			key = ftok (((ptrKeys + i)->args)[0], 0);
			keyFlag = 1;
		}
	}

	if (key < 0)
	{
		return -1;
	}

	if (!keyFlag)
	{
		key = ftok ("keyfile", 0);
	}

	return key;
}


int GetSemId (const int key, const int keyCount)
{
	assert (key >= 0);
	assert (keyCount >= 0);

	int semId = semget (key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if (semId < 0)
	{
		semId = semget (key, 1, 0666);
	}
	else
	{
		IncSem (semId);
	}

	return semId;
}

int GetShmId (const int key, const int keyCount)
{
	assert (key >= 0);
	assert (keyCount >= 0);

	const int sizeSharedMem = 2 * sizeof (long long int);
	int shmId = shmget (key, sizeSharedMem, IPC_CREAT | IPC_EXCL | 0666);
	if (shmId < 0)
	{
		shmId = shmget (key, sizeSharedMem, 0666);
	}
	else
	{
		int i = 0;
		char* data = shmat (shmId, NULL, 0);
		for (i = 0; i < sizeSharedMem; i++)
		{
			data[i] = 0;
		}
		shmdt (data);
	}

	return shmId;
}



void Calculating (long long int* data, const int semId)
{
	assert (data);
	assert (semId >= 0);

	time_t currTime = 0;
	srand ((unsigned) time (&currTime));

	long long int yesCounter = 0;
	long long int noCounter = 0;
	long double x = 0;
	long double y = 0;

	long long int i = 0;
	for (i = 1; i <= 100000000; i++)
	{
		x = -(long double) 1.0 + (long double) 2.0 * ((long double) rand () / (long double) RAND_MAX);
		y = -(long double) 1.0 + (long double) 2.0 * ((long double) rand () / (long double) RAND_MAX);

		if (x * x + y * y < 1)
		{
			yesCounter++;
		}
		else
		{
			noCounter++;
		}

		if (i % 10000 == 0)
		{
			DecSem (semId);
			data[0] = data[0] + yesCounter;
			data[1] = data[1] + noCounter;
			IncSem (semId);
			yesCounter = 0;
			noCounter = 0;
		}
	}
}



void CheckCalculateKey (const int keyCount, struct Key* ptrKeys, long long int* data, const int semId)
{
	assert (keyCount >= 0);
	assert (ptrKeys);
	assert (data);
	assert (semId >= 0);

	int i = 0;
	for (i = 0; i < keyCount; i++)
	{
		if ((ptrKeys + i)->type == KEYTYPE_CALC)
		{
			Calculating (data, semId);
		}
	}

}


void CheckHelpKey (const int keyCount, struct Key* const ptrKeys)
{
	assert (keyCount >= 0);
	assert (ptrKeys);

	int i = 0;
	for (i = 0; i < keyCount; i++)
	{
		if ((ptrKeys + i)->type == KEYTYPE_HELP)
		{
			PrintHelp ();
		}
	}
}


void CheckPrintKey (const int keyCount, struct Key* const ptrKeys, long long int* data)
{
	assert (keyCount >= 0);
	assert (ptrKeys);
	assert (data);

	int i = 0;
	for (i = 0; i < keyCount; i++)
	{
		if ((ptrKeys + i)->type == KEYTYPE_PRINT)
		{	
			long double pi = 4 * ((long double) data[0] / (long double) (data[0] + data[1]));
			printf ("yesCounter = %lld\n", data[0]);
			printf ("noCounter = %lld\n", data[1]);
			printf ("pi = %Lf\n", pi);
		}
	}
}


void CheckResetKey (const int keyCount, struct Key* const ptrKeys, const int semId, const int shmId)
{
	assert (keyCount >= 0);
	assert (ptrKeys);
	assert (semId >= 0);
	assert (shmId >= 0);

	int i = 0;
	for (i = 0; i < keyCount; i++)
	{
		if ((ptrKeys + i)->type == KEYTYPE_RESET)
		{
			shmctl (shmId, IPC_RMID, NULL);
			semctl (semId, 0, IPC_RMID, 0);
		}
	}
}



