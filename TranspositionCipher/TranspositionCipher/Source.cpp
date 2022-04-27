#include<iostream>

#include <winsock2.h>	
#include <ws2tcpip.h>	

#pragma comment(lib, "Ws2_32.lib")	

int main()
{

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return 1;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;


	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket listenning! error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}


	addrinfo* result = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;

#define DEFAULT_PORT "27015"


	iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		std::cout << "Getaddrinfo failed:" << iResult << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}


	iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Failed to connect to server!!:\n";
		WSACleanup();
		return 1;
	}


#define DEFAULT_BUFLEN 512

	int recvbuflen = DEFAULT_BUFLEN;

	const char* sendbuf = "alex e smecher";
	char recvbuf[DEFAULT_BUFLEN];


	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "Bytes Sent: " << iResult << std::endl;


	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "shutdown failed..." << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}


	do
	{
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			std::cout << "Bytes received: " << iResult << std::endl;

			std::cout << "Buffer content: ";
			for (int i = 0; i < iResult; i++)
				std::cout << recvbuf[i];
			std::cout << std::endl;

		}
		else if (iResult == 0)
			std::cout << "Connection closed..." << std::endl;
		else
			std::cout << "recv failed..." << WSAGetLastError() << std::endl;
	} while (iResult > 0);


	closesocket(ConnectSocket);
	WSACleanup();
	system("pause");
	return 0;
}

