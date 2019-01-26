// 472 Mikhalev Artem 26.09.2015

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "serverclient.h"


enum KEY_t
{
	KEY_CLIENT = 0,
	KEY_SERVER = 1,
	KEY_ERROR  = 2
};

int  GetKey (const int argc, char** const agrv);


int main (int argc, char** argv, char** env)
{
	mkfifo ("cl2ser.fifo", 0777);
	mkfifo ("ser2cl.fifo", 0777);

	int pipeRequest = 0;
	int pipeAnswer = 0;

	switch (GetKey (argc, argv))
	{
		case KEY_CLIENT:
			pipeRequest = open ("cl2ser.fifo", O_WRONLY);
			pipeAnswer = open ("ser2cl.fifo", O_RDONLY);
			WorkClient (pipeRequest, pipeAnswer);
			break;
		case KEY_SERVER:
			pipeRequest = open ("cl2ser.fifo", O_RDONLY);
			pipeAnswer = open ("ser2cl.fifo", O_WRONLY);
			WorkServer (pipeRequest, pipeAnswer);
			break;
		default:
			printf ("ERROR. Incorrect key.\n");
			break;
	}

	close (pipeRequest);
	close (pipeAnswer);

	return 0;
}


int GetKey (const int argc, char** const argv)
{
	assert (argv);
	if (argc != 2)
	{
		return KEY_ERROR;
	}

	if (!strcmp (argv[1], "-s"))
	{
        	return KEY_SERVER;
	}
	if (!strcmp (argv[1], "-c"))
	{
        	return KEY_CLIENT;
	}

	return KEY_ERROR;
}





