#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

const int SHARED_MEM_SIZE = 1024;

enum Errors_t
{
	ERR_HAPPINESS          = 0,
	ERR_WRONG_ARGS_AMOUNT  = 1,
	ERR_KEY_FILE           = 2,
	ERR_CREAT_SHARED_MEM   = 3,
	ERR_ATTEMPT_SHARED_MEM = 4,
	ERR_ACCESS_SHARED_MEM  = 5,
	ERR_INPUT_FILE         = 6,
	ERR_OTHER              = 7
};


int FillSharedMem (char** argv);
int ReadSharedMem (char** argv);



int main (int argc, char** argv, char** env)
{
	int errNum = ERR_WRONG_ARGS_AMOUNT;
	if (argc == 3)
	{	
		errNum = FillSharedMem (argv);
	}
	if (argc == 2)
	{
		errNum = ReadSharedMem (argv);
	}

	switch (errNum)
	{
		case ERR_HAPPINESS:                                                                           break;
		case ERR_WRONG_ARGS_AMOUNT:  printf ("ERROR. Wrong amount of command line's arguments.\n");   break;
		case ERR_KEY_FILE:           printf ("ERROR. Problems with the key file.\n");                 break;
		case ERR_CREAT_SHARED_MEM:   printf ("ERROR. Can't create shared memory.\n");                 break;
		case ERR_ATTEMPT_SHARED_MEM: printf ("ERROR. Can't access to shared memory.\n");              break;
		case ERR_ACCESS_SHARED_MEM:  printf ("ERROR. Problems with access to shared memory.\n");      break;
		case ERR_INPUT_FILE:         printf ("ERROR. Can't open your input file.\n");                 break;
		default:                     printf ("ERROR. But I don't know anything about this error.\n"); break;
	}

	return 0;
}




int FillSharedMem (char** argv)
{
	assert (argv);
	assert (argv[1]);
	assert (argv[2]);

	int key = ftok (argv[2], 0);
	if (key < 0)
	{
		return ERR_KEY_FILE;
	}

	int shmId = shmget (key, SHARED_MEM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
	if (shmId < 0)
	{
		return ERR_CREAT_SHARED_MEM;
	}

	char* data = shmat (shmId, NULL, 0);
	if (data <= (char*) 0)
	{
		return ERR_ATTEMPT_SHARED_MEM;
	}

	int fileDes = open (argv[1], O_RDONLY);
	if (fileDes < 0)
	{
		return ERR_INPUT_FILE;
	}

	int i = 0;
	int readRes = 1;
	while (readRes)
	{
		readRes = read (fileDes, data + i, sizeof (char));
		i++;
	}

	close (fileDes);
	shmdt (data);
	return ERR_HAPPINESS;
}


int ReadSharedMem (char** argv)
{
	assert (argv);
	assert (argv[1]);

	int key = ftok (argv[1], 0);
	if (key < 0)
	{
		return ERR_KEY_FILE;
	}

	int shmId = shmget (key, SHARED_MEM_SIZE, 0666);
	if (shmId < 0)
	{
		return ERR_ACCESS_SHARED_MEM;
	}

	char* data = shmat (shmId, NULL, 0);
	if (data <= (char*) 0)
	{
		return ERR_ATTEMPT_SHARED_MEM;
	}

	printf ("%s\n", data);

	shmdt (data);
	shmctl (shmId, IPC_RMID, NULL);
	return ERR_HAPPINESS;
}




