#include <iostream>
#include <winsock2.h>
#include <assert.h>
#include <thread>
#include <list>

#include "Client.h"

#pragma comment (lib, "Ws2_32.lib")

static const int port = 5010;

void InitWinSockLibrary();
SOCKET CreateMainServerSocket(struct sockaddr_in* serverInfo);
void DetachDisconnectedClients(std::list<Client*>& clients);
void ExitProgram(const int errorCode);



int main()
{
	// Initialise winsock library
	InitWinSockLibrary();

	struct sockaddr_in serverInfo = {};
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(port);

	// Create a socket, then bind it
	SOCKET mainServerSocket = CreateMainServerSocket(&serverInfo);

	// Listen to incoming connections
	listen(mainServerSocket, SOMAXCONN);
	std::cout << "Server started. Listening..." << std::endl;

	std::list<Client*> clients;
	SOCKET newClientSocket = NULL;
	struct sockaddr_in newClientInfo = {};
	int aux = sizeof(struct sockaddr_in);

	for (;;)
	{
		newClientSocket = accept(mainServerSocket,
			(struct sockaddr *)&newClientInfo,
			&aux);
		if (newClientSocket == INVALID_SOCKET)
		{
			std::cout << "accept failed with error code : "
				<< WSAGetLastError() << std::endl;
		}

		Client* newClient = new Client(newClientSocket);
		clients.push_back(newClient);
		if (newClient->CreateConsoleProcess() != 0)
		{
			std::cout << "Could not run threads for new client" << std::endl;
			newClient->clientSocket_ = INVALID_SOCKET;
		}

		DetachDisconnectedClients(clients);
	}

	closesocket(mainServerSocket);
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



SOCKET CreateMainServerSocket(struct sockaddr_in* serverInfo)
{
	assert(serverInfo);

	SOCKET mainServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mainServerSocket == INVALID_SOCKET)
	{
		std::cout << "Could not create socket : "
			<< WSAGetLastError() << std::endl;
		ExitProgram(1);
	}

	if (bind(mainServerSocket,
		(struct sockaddr*)serverInfo,
		sizeof(*serverInfo)) == SOCKET_ERROR)
	{
		std::cout << "Bind failed with error code : "
			<< WSAGetLastError() << std::endl;
		ExitProgram(1);
	}

	return mainServerSocket;
}



void DetachDisconnectedClients(std::list<Client*>& clients)
{
	std::list<Client*>::iterator it;
	char auxByte = 0;

	for (it = clients.begin(); it != clients.end(); it++)
	{
		assert(*it);

		if ((*it)->clientSocket_ == INVALID_SOCKET)
		{
			delete *it;
			it = clients.erase(it);
		}
	}
}



void ExitProgram(const int errorCode)
{
	system("pause");
	ExitProcess(errorCode);
}

