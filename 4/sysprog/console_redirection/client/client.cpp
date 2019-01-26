#include <winsock2.h>
#include <assert.h>
#include <iostream>
#include <thread>

#pragma comment (lib, "ws2_32.lib")

#define BUFSIZE 4096

static const char exitCommand[] = "exit";
static const int port = 5010;

void InitWinSockLibrary();
void GetServerIPAddress(char* serverIPAddress);
void ConnectToServer(SOCKET clientSocket, struct sockaddr_in* serverInfo);
void ProcessClient(SOCKET clientSocket);
void ExitProgram(const int errorCode);



int main()
{
	// Initialise winsock library
	InitWinSockLibrary();

	// Get IP-address to connect
	char serverIPAddress[BUFSIZE] = {};
	GetServerIPAddress(serverIPAddress);

	// Create a socket
	SOCKET clientSocket = NULL;
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		std::cout << "Could not create socket : " << WSAGetLastError() << std::endl;
		ExitProgram(1);
	}

	struct sockaddr_in serverInfo = {};
	serverInfo.sin_addr.s_addr = inet_addr(serverIPAddress);
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(port);

	// Connect to server
	std::cout << "Connecting to server (" << serverIPAddress << ") ..." << std::endl;
	ConnectToServer(clientSocket, &serverInfo);

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
	{
		std::cout << "Could not get handle of stdin" << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		ExitProgram(1);
	}

	std::thread recvThread(ProcessClient, std::ref(clientSocket));

	char sendBuf[BUFSIZE] = {};
	DWORD numberOfReadBytes = 0;

	// Reading commands from console
	for (;;)
	{
		if (ReadFile(hStdin, sendBuf, BUFSIZE, &numberOfReadBytes, NULL) == 0)
		{
			std::cout << "Could not read from console" << std::endl;
			break;
		}

		if (sendBuf[BUFSIZE - 1] != 0)
		{
			std::cout << "Too long command. Try again" << std::endl;
			continue;
		}

		if (send(clientSocket, sendBuf, numberOfReadBytes, 0) < 0)
		{
			std::cout << "send failed: " << WSAGetLastError() << std::endl;
			break;
		}

		if (strncmp(sendBuf, exitCommand, strlen(exitCommand) - 1) == 0)
		{
			std::cout << "Exiting from remote console ..." << std::endl;
			break;
		}
	}

	std::cout << "Shutting down ..." << std::endl;
	recvThread.detach();
	closesocket(clientSocket);
	WSACleanup();

	system("pause");
	return 0;
}



void InitWinSockLibrary()
{
	WSAData wsaData = {};

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Failed to initialise winsock library" << std::endl;
		ExitProgram(1);
	}
}



void GetServerIPAddress(char* serverIPAddress)
{
	assert(serverIPAddress);

	std::cout << "Type IP-address: " << std::flush;
	std::cin >> serverIPAddress;

	if (serverIPAddress[BUFSIZE - 1] != 0)
	{
		std::cout << "Too long input. Exiting ..." << std::endl;
		ExitProgram(1);
	}
}



void ConnectToServer(SOCKET clientSocket, struct sockaddr_in* serverInfo)
{
	assert(clientSocket);
	assert(serverInfo);

	while (connect(clientSocket, (struct sockaddr*)serverInfo, sizeof(*serverInfo)) < 0)
	{
		Sleep(100);
	}

	std::cout << "Connected" << std::endl;
}



void ProcessClient(SOCKET clientSocket)
{
	assert(clientSocket);

	char recvBuf[BUFSIZE + 1] = {};
	DWORD recvSize = 0;

	for (;;)
	{
		memset(recvBuf, 0, BUFSIZE + 1);

		// Recieving server's response
		if ((recvSize = recv(clientSocket, recvBuf, BUFSIZE, 0)) == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAECONNABORTED)
			{
				std::cout << "Connection aborted" << std::endl;
			}
			else
			{
				std::cout << "recv failed: " << WSAGetLastError() << std::endl;
			}

			break;
		}

		// Printing recieved message
		std::cout << recvBuf;
	}

	if (WSAGetLastError() == WSAECONNRESET)
	{
		std::cout << "Server disconnected" << std::endl;
	}
}



void ExitProgram(const int errorCode)
{
	system("pause");
	ExitProcess(errorCode);
}

