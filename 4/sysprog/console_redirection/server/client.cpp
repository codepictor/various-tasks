#include "client.h"

static const char exitCommand[] = "exit";



Client::Client(SOCKET clientSocket)
{
	clientSocket_ = clientSocket;
}



Client::~Client()
{
	if (pipeInRead_)
	{
		CloseHandle(pipeInRead_);
	}
	if (pipeInWrite_)
	{
		CloseHandle(pipeInWrite_);
	}
	if (pipeOutRead_)
	{
		CloseHandle(pipeOutRead_);
	}
	if (pipeOutWrite_)
	{
		CloseHandle(pipeOutWrite_);
	}
}



int Client::CreateConsoleProcess()
{
	SECURITY_ATTRIBUTES sa = {};
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	if (!CreatePipe(&pipeInRead_, &pipeInWrite_, &sa, 0))
	{
		std::cout << "ERROR! Could not create pipe" << std::endl;
		return -1;
	}

	if (!CreatePipe(&pipeOutRead_, &pipeOutWrite_, &sa, 0))
	{
		std::cout << "ERROR! Could not create pipe" << std::endl;
		return -1;
	}

	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = pipeOutWrite_;
	si.hStdError = pipeOutWrite_;
	si.hStdInput = pipeInRead_;

	// Start the child process.
	TCHAR lpCommandLine[] = TEXT("cmd.exe");
	if (!CreateProcess(NULL,  // No module name (use command line)
		lpCommandLine,        // Command line
		NULL,                 // Process handle not inheritable
		NULL,				  // Thread handle not inheritable
		TRUE,                 // Set handle inheritance to True
		0,                    // No creation flags
		NULL,                 // Use parent's environment block
		NULL,                 // Use parent's starting directory 
		&si,                  // Pointer to STARTUPINFO structure
		&pi)                  // Pointer to PROCESS_INFORMATION structure
		)
	{
		std::cout << "CreateProcess failed : " << GetLastError() << std::endl;
		return -1;
	}
	else
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	sendThread_ = std::thread(WriteToPipe, this);
	recvThread_ = std::thread(ReadFromPipe, this);
	sendThread_.detach();
	recvThread_.detach();

	return 0;
}



void ReadFromPipe(Client* client)
{
	assert(client);

	char buf[BUFSIZE + 1] = {};
	DWORD numberOfBytesRead = 0;

	for (;;)
	{
		memset(buf, 0, BUFSIZE + 1);

		if (ReadFile(client->pipeOutRead_, buf, BUFSIZE, &numberOfBytesRead, NULL) == 0)
		{
			client->clientSocket_ = INVALID_SOCKET;
			break;
		}

		std::cout << buf << std::flush;

		if (client->clientSocket_ != NULL && client->clientSocket_ != INVALID_SOCKET)
		{
			send(client->clientSocket_, buf, numberOfBytesRead, 0);
		}
		else
		{
			client->clientSocket_ = INVALID_SOCKET;
			break;
		}
	}
}



void WriteToPipe(Client* client)
{
	assert(client);

	char buf[BUFSIZE] = {};
	DWORD recvSize = 0;
	DWORD numberOfBytesWritten = 0;

	for (;;)
	{
		recvSize = recv(client->clientSocket_, buf, BUFSIZE, 0);

		if (recvSize == SOCKET_ERROR)
		{
			std::cout << "Could not recieve data from socket: "
				<< WSAGetLastError() << std::endl;
			client->clientSocket_ = INVALID_SOCKET;
			break;
		}

		if (strncmp(buf, exitCommand, strlen(exitCommand) - 1) == 0)
		{
			const char exit[] = "exit\r\n";
			if (WriteFile(client->pipeInWrite_,
				exit, strlen(exit), &numberOfBytesWritten, NULL) == 0)
			{
				std::cout << "Could not close console" << std::endl;
			}

			client->clientSocket_ = INVALID_SOCKET;
			break;
		}

		if (recvSize != 0 && WriteFile(client->pipeInWrite_,
			buf, recvSize, &numberOfBytesWritten, NULL) == 0)
		{
			std::cout << "Could not execute: " << buf << std::endl;
			client->clientSocket_ = INVALID_SOCKET;
			break;
		}
	}
}

