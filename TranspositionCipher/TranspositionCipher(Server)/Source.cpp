#include<iostream>

#include <winsock2.h>	
#include <ws2tcpip.h>	
#pragma comment(lib, "Ws2_32.lib")	
#define DEFAULT_PORT "27015"

int main()
{

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return 1;
	}


	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket listenning! error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	struct addrinfo* result = NULL, * ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		std::cout << "Getaddrinfo failed:" << iResult << std::endl;
		WSACleanup();
		return 1;
	}


	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Binding failed" << std::endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);


	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	SOCKET ClientSocket = INVALID_SOCKET;
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	closesocket(ListenSocket);


#define DEFAULT_BUFLEN 512
	char recvbuf[DEFAULT_BUFLEN];
	char sendbuf[DEFAULT_BUFLEN];
	int iRecvResult, iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;


	do
	{

		iRecvResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iRecvResult > 0)
		{
			std::cout << "Bytes received: " << iRecvResult << std::endl;

			std::cout << "Buffer content: ";
			for (int i = 0; i < iRecvResult; i++)
				std::cout << recvbuf[i];
			std::cout << std::endl;


			sprintf_s(sendbuf, "Thank you, I received %d bytes from you!", iRecvResult);
			iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
			if (iSendResult == SOCKET_ERROR)
			{
				std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			std::cout << "Bytes sent: " << iSendResult << std::endl;
		}
		else if (iRecvResult == 0)
			std::cout << "Connection closing..." << std::endl;
		else
		{
			std::cout << "recv failed..." << WSAGetLastError() << std::endl;
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iRecvResult > 0);

	
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		std::cout << "shutdown failed..." << WSAGetLastError() << std::endl;
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}


	closesocket(ClientSocket);
	WSACleanup();
	system("pause");
	return 0;
}
