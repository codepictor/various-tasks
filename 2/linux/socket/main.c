#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>


#define MSG_LEN 1024


void* ThreadMain (void* args)
{
	assert (args);

	int socketDesc = socket (AF_INET, SOCK_DGRAM, 0);
printf ("thread desc = %d\n", socketDesc);

	struct sockaddr_in destAddress = {};

	destAddress.sin_family = AF_INET;
	if (*(int*) args == 1)
	{
		destAddress.sin_port = htons (60000);
	}
	else
	{
		destAddress.sin_port = htons (60001);
	}
	inet_aton ("127.0.0.1", &(destAddress.sin_addr));

	char str [MSG_LEN] = {};
	int len = 0;

	while (1)
	{
		scanf ("%s", str);
		len = strlen (str);
		sendto (socketDesc, str, len + 1, 0, (struct sockaddr*) &destAddress, sizeof (destAddress));
		str[len] = 0;
	}
}






int main (int argc, char** argv, char** env)
{
	assert (argc == 2);
	int number = 0;
	sscanf (argv[1] + 1, "%d", &number);

	int socketDesc = socket (AF_INET, SOCK_DGRAM, 0);
printf ("main desc = %d\n", socketDesc);

	pthread_t threadId = 0;
	pthread_create (&threadId, NULL, ThreadMain, &number);

	struct sockaddr_in myAddress = {};
	myAddress.sin_family = AF_INET;
	if (number == 1)
	{
		myAddress.sin_port = htons (60001);
	}
	else
	{
		myAddress.sin_port = htons (60000);
	}
	inet_aton ("127.0.0.1", &(myAddress.sin_addr));

	bind (socketDesc, (struct sockaddr*) &myAddress, sizeof (myAddress));

	char str [MSG_LEN] = {};
	while (1)
	{
		recvfrom (socketDesc, str, MSG_LEN, 0, 0, 0);
		printf ("%s\n", str);
	}


	return 0;
}
