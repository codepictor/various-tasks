// 472 Mikhalev Artem 26.09.2015

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

const int PIECE_STRING = 16;

enum KEY_t
{
	KEY_CLIENT = 0,
	KEY_SERVER = 1,
	KEY_ERROR  = 2
};

int  GetKey         (const int argc, char** const agrv);
void WorkClient     ();
void WorkServer     ();
int  GetCountSymbol (const char* const str, const int asciiCode);



int main (int argc, char** argv, char** env)
{
	mkfifo ("cl2ser.fifo", 0777);
	mkfifo ("ser2cl.fifo", 0777);
	
	int key = GetKey (argc, argv);
	switch (key)
	{
		case KEY_CLIENT:
			WorkClient ();
			break;
		case KEY_SERVER:
			WorkServer ();
			break;
		default:
			printf ("ERROR. Incorrect key.\n");
			break;
	}

	return 0;
}


int GetKey (const int argc, char** const argv)
{
	assert (argv);
	if (argc != 2)
	{
		return KEY_ERROR;
	}

	if (*(argv[1]) == '-' && *(argv[1] + 2) == 0)
	{
		if (*(argv[1] + 1) == 'c')
		{
			return KEY_CLIENT;
		}
		if (*(argv[1] + 1) == 's')
		{
			return KEY_SERVER;
		}
	}

	return KEY_ERROR;
}



void WorkClient ()
{
	int pipeRequest = open ("cl2ser.fifo", O_WRONLY);
	int pipeAnswer = open ("ser2cl.fifo", O_RDONLY);

	char inputData[1000] = {};
	scanf ("%s", inputData);
	int i = 0;
	int flag = 1;

	while (flag)
	{
		if (inputData[i] == 0)
		{
			flag = 0;
		}
		write (pipeRequest, inputData + i, PIECE_STRING);
		i = i + PIECE_STRING;
	}

	int res = 0;
	read (pipeAnswer, &res, sizeof (int));
	printf ("Amount of symbol 'a' = %d\n", res);

	close (pipeRequest);
	close (pipeAnswer);
}

void WorkServer ()
{
	int pipeRequest = open ("cl2ser.fifo", O_RDONLY);
	int pipeAnswer = open ("ser2cl.fifo", O_WRONLY);

	char* str = (char*) calloc (PIECE_STRING, sizeof (char));
	assert (str);
	
	int flag = 1;
	int res = 0;
	while (flag)
	{
		read (pipeRequest, str, PIECE_STRING);
		res = res + GetCountSymbol (str, 'a');
		if (str[0] == 0)
		{
			flag = 0;
		}
	}


	write (pipeAnswer, &res, sizeof (int));

	free (str);
	str = NULL;

	close (pipeRequest);
	close (pipeAnswer);
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


