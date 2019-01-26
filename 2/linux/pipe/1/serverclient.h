// 472 Mikhalev Artem 26.09.15

#include <string.h>
#include <stdio.h>

const int PIECE_STRING = 16;

void WorkClient     (int pipeRequest, int pipeAnswer);
void WorkServer     (int pipeRequest, int pipeAnswer);
int  GetCountSymbol (const char* const str, const int asciiCode);


void WorkClient (int pipeRequest, int pipeAnswer)
{
	char inputData[1000] = {};
	scanf ("%s", inputData);
	int i = 0;
	int waitedSymbols = strlen (inputData);
	int countMessages = waitedSymbols / PIECE_STRING + 1;

	for (i = 0; i < countMessages; i++)
	{
		if (waitedSymbols >= 16)
		{
			write (pipeRequest, &PIECE_STRING, sizeof (int));
		}
		else
		{
			write (pipeRequest, &waitedSymbols, sizeof (int));
		}
		write (pipeRequest, inputData + i * PIECE_STRING, PIECE_STRING);
		waitedSymbols = waitedSymbols - PIECE_STRING;
	}

	int res = 0;
	read (pipeAnswer, &res, sizeof (int));
	printf ("Amount of symbol 'a' = %d\n", res);
}

void WorkServer (int pipeRequest, int pipeAnswer)
{
	char* str = (char*) calloc (PIECE_STRING, sizeof (char));
	assert (str);
	int res = 0;
	int lenMessage = PIECE_STRING;

	while (lenMessage == PIECE_STRING)
	{
		read (pipeRequest, &lenMessage, sizeof (int));
		read (pipeRequest, str, PIECE_STRING);
		res = res + GetCountSymbol (str, 'a');
	}

	write (pipeAnswer, &res, sizeof (int));

	free (str);
	str = NULL;
}


int GetCountSymbol (const char* const str, const int asciiCode)
{
	assert (str);
	assert (0 <= asciiCode && asciiCode <= 255);

	int i = 0;
	int count = 0;
	while (str[i] != 0)
	{
		if (str[i] == asciiCode)
		{
			count++;
		}
		i++;
	}

	return count;
}

