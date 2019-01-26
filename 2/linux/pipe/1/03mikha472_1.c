// 472 Mikhalev Artem 26.09.2015

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "serverclient.h"

int* CreatePipe ();
void DeletePipe (int* pipeArray);


int main ()
{
	int* pipeRequest = CreatePipe ();
	int* pipeAnswer = CreatePipe ();
	int forkRes = fork ();
	if (forkRes < 0)
	{
		printf ("ERROR. Can't fork.\n");
		exit (1);
	}

	if (forkRes > 0)
	{
		close (pipeRequest[0]);
		close (pipeAnswer[1]);
		WorkClient (pipeRequest[1], pipeAnswer[0]);
		close (pipeRequest[1]);
		close (pipeAnswer[0]);
	}
	else
	{
		close (pipeRequest[1]);
		close (pipeAnswer[0]);
		WorkServer (pipeRequest[0], pipeAnswer[1]);
		close (pipeRequest[0]);
		close (pipeAnswer[1]);
	}

	DeletePipe (pipeRequest);
	DeletePipe (pipeAnswer);

	return 0;
}


int* CreatePipe ()
{
	int* pipeArray = (int*) calloc (2, sizeof (int));
	assert (pipeArray);

	int pipeRes = pipe (pipeArray);
	if (pipeRes)
	{
		printf ("ERROR. Can't create pipe.\n");
		exit (1);
	}

	return pipeArray;
}

void DeletePipe (int* pipeArray)
{
	assert (pipeArray);

	free (pipeArray);
	pipeArray = NULL;
}


