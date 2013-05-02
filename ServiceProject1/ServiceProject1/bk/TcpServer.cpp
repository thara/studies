#include <WinSock2.h>
#include <WS2tcpip.h>
#include "TcpServer.h"

#include "demo_service.h"



TcpServer::TcpServer(void){
	createTcpServer();
}


TcpServer::~TcpServer(void){
	quitTcpServer();
}

void TcpServer::quitTcpServer() {
	WSACleanup();
	DebugPrint (TEXT("�T�[�o�[���I�����܂����B\n"));
}

void TcpServer::createTcpServer(){
	
	dstAddrSize = sizeof(dstAddr);
	
	// Windows �̏ꍇ
	WSAStartup(MAKEWORD(2,0), &data);
	// sockaddr_in �\���̂̃Z�b�g
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(PORT);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// �\�P�b�g�̐����i�X�g���[���^�j
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);
  	// �\�P�b�g�̃o�C���h
	bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));
  	// �ڑ��̋���
	listen(srcSocket, 1);
}

void TcpServer::startService(){
	while(1){ //���[�v�ŉ񂷂��Ƃɂ���ĉ��x�ł��N���C�A���g����Ȃ����Ƃ��ł���

		// �ڑ��̎�t��

    DebugPrint (TEXT("�ڑ���҂��Ă��܂�\n�N���C�A���g�v���O�����𓮂����Ă�������\n"));
		dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
	  DebugPrint (TEXT("�ڑ����󂯂܂���\n"));

		while(1){
			//�p�P�b�g�̎�M
			numrcv = recv(dstSocket, buffer, sizeof(char)*1024, 0);
			if(numrcv ==0 || numrcv ==-1 ){
				status = closesocket(dstSocket); break;
			}
//			printf("�ϊ��O %s",buffer);


			for (int i=0; i< numrcv; i++){ // buf�̒��̏�������啶���ɕϊ�
				//if(isalpha(buffer[i])) 
					buffer[i] = toupper(buffer[i]);
			}
			// �p�P�b�g�̑��M
			send(dstSocket, buffer, sizeof(char)*1024, 0);
		  DebugPrint (TEXT("�ϊ���̒l��ԋp���܂����B\n"));

			//			printf("�� �ϊ��� %s \n",buffer);
		}
	}
}