
#include <winsock2.h>	
#include <ws2tcpip.h>	
#include "Encryption.h"
#pragma comment(lib, "Ws2_32.lib")	

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512


int main()
{
	
	Encryption  encryption("copil", "laboratorul de retele de calculatoare");
	encryption.PrintEncryptionData();
	encryption.EncryptMessage();
	std::cout << encryption.GetEncryptedMessage() << std::endl;
	
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


	std::string message;
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	do {


		std::cout << "Introduceti mesajul : \n";
		std::cin >> message;
		const char* sendbuf = message.c_str();


		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		if (iResult == SOCKET_ERROR)
		{
			std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		std::cout << "Bytes Sent: " << iResult << std::endl;
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			std::cout << "Bytes received: " << iResult << std::endl;

			std::cout << "Buffer content: ";
			for (int i = 0; i < iResult; i++)
				std::cout << recvbuf[i];
			std::cout << std::endl;

		}
	} while (message != "close");

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "shutdown failed..." << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	closesocket(ConnectSocket);
	WSACleanup();
	system("pause");
	return 0;
}

