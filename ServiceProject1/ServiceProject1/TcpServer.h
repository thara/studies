#pragma once
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define PORT 9876

class TcpServer
{
public:
	TcpServer();
	~TcpServer(void);
	void createTcpServer(void);
	void quitTcpServer(void);
	void startService(void);

	static int counter;

private:
	int srcSocket;  // �����̃\�P�b�g
	int dstSocket;  // ����̃\�P�b�g
	// sockaddr_in �\����
	struct sockaddr_in srcAddr;
	struct sockaddr_in dstAddr;
	int dstAddrSize;
	// �e��p�����[�^
	int numrcv;
	char buffer[1024];
	int status;
	WSADATA data;

		/*
typedef struct sockaddr_in {
#if(_WIN32_WINNT < 0x0600)
    short   sin_family;
#else //(_WIN32_WINNT < 0x0600)
    ADDRESS_FAMILY sin_family;
#endif //(_WIN32_WINNT < 0x0600)

    USHORT sin_port;
    IN_ADDR sin_addr;
    CHAR sin_zero[8];
} SOCKADDR_IN, *PSOCKADDR_IN;
	*/

};
