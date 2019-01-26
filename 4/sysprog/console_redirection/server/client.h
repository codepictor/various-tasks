#pragma once

#include <thread>
#include <winsock2.h>
#include <iostream>
#include <assert.h>
#include <windows.h> 

#define BUFSIZE 4096


class Client
{
public:
	explicit Client(SOCKET clientSocket);
	virtual ~Client();

	int CreateConsoleProcess();

	SOCKET clientSocket_ = NULL;

	HANDLE pipeInRead_ = NULL;
	HANDLE pipeInWrite_ = NULL;
	HANDLE pipeOutRead_ = NULL;
	HANDLE pipeOutWrite_ = NULL;

	std::thread recvThread_;
	std::thread sendThread_;
};


void ReadFromPipe(Client* client);
void WriteToPipe(Client* client);

