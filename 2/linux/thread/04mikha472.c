// 472 Mikhalev Artem 03.10.2015

#define ARRAY_SIZE 1000000
#define THREADS_COUNT 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>

//const int THREADS_COUNT = 10;
//const int ARRAY_SIZE = 30;
const int POISON = -1;

struct ThreadInfo
{
	int threadIndex;
	int* arrayStart;
	int* arrayEnd;
	pthread_t threadId;
};


int   Compar          (const void* a, const void* b);
void* ThreadMain      (void* args);
void  MergeArray      (int* const array, const int arrayPiece);

//int array[ARRAY_SIZE] = {};
//int resArray[ARRAY_SIZE] = {};

int main ()
{
	int array[ARRAY_SIZE] = {};
	int i = 0;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		scanf ("%d", array + i);
	}

	struct ThreadInfo threadInfos[THREADS_COUNT] = {};
	const int arrayPiece = ARRAY_SIZE / THREADS_COUNT;

	for (i = 0; i < THREADS_COUNT; i++)
	{
		threadInfos[i].threadIndex = i;
		threadInfos[i].arrayStart = array + i * arrayPiece;
		if (i == THREADS_COUNT - 1)
		{
			threadInfos[i].arrayEnd = array + ARRAY_SIZE - 1;
		}
		else
		{
			threadInfos[i].arrayEnd = array + (i + 1) * arrayPiece - 1;
		}
		pthread_create (&(threadInfos[i].threadId), 0, ThreadMain, threadInfos + i);
	}

	for (i = 0; i < THREADS_COUNT; i++)
	{
		pthread_join (threadInfos[i].threadId, NULL);
	}

//	MergeArray (array, arrayPiece);

	/*printf ("result\n");
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		printf ("%d ", array[i]);
	}
	printf ("\n");*/

//	printf ("time = %d\n", (int) clock ());
	return 0;
}



int Compar (const void* firstNum, const void* secondNum)
{
	assert (firstNum);
	assert (secondNum);

	return *(int*)firstNum - *(int*)secondNum;
}


void* ThreadMain (void* args)
{
	assert (args);
	struct ThreadInfo thread = *(struct ThreadInfo*) args;
	assert (thread.arrayStart);
	assert (thread.arrayEnd);
	assert (thread.arrayStart <= thread.arrayEnd);

	qsort (thread.arrayStart, thread.arrayEnd - thread.arrayStart + 1, sizeof (int), Compar);
}


void MergeArray (int* const array, const int arrayPiece)
{
	assert (array);
	assert (0 < arrayPiece && arrayPiece <= ARRAY_SIZE);
	
	const int sizeLast = ARRAY_SIZE - (THREADS_COUNT - 1) * arrayPiece;
	const int lastIndex = THREADS_COUNT - 1;
	int arrayHead[THREADS_COUNT] = {};
	int resArray[ARRAY_SIZE] = {};
	int minElem = 0;
	int pieceNum = 0;
	int flag = 0;
	int i = 0;
	int j = 0;

	for (i = 0; i < ARRAY_SIZE; i++)
	{
		flag = 1;
		for (j = 0; j < THREADS_COUNT; j++)
		{
			if (arrayHead[j] != POISON)
			{
				if (flag)
				{
					minElem = array[arrayHead[j] + j * arrayPiece];
					flag = 0;
				}

				if (array[arrayHead[j] + j * arrayPiece] <= minElem)
				{
					minElem = array[arrayHead[j] + j * arrayPiece];
					pieceNum = j;
				}
			}
		}

		arrayHead[pieceNum]++;
		if (((arrayHead[pieceNum] % arrayPiece == 0) && (pieceNum != lastIndex)) || ((pieceNum == lastIndex) && (arrayHead[pieceNum] == sizeLast)))
		{
			arrayHead[pieceNum] = POISON;
		}
		resArray[i] = minElem;
	}

	memcpy (array, resArray, ARRAY_SIZE * sizeof (int));
}



