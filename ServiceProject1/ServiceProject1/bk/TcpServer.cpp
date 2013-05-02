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
	DebugPrint (TEXT("サーバーを終了しました。\n"));
}

void TcpServer::createTcpServer(){
	
	dstAddrSize = sizeof(dstAddr);
	
	// Windows の場合
	WSAStartup(MAKEWORD(2,0), &data);
	// sockaddr_in 構造体のセット
	memset(&srcAddr, 0, sizeof(srcAddr));
	srcAddr.sin_port = htons(PORT);
	srcAddr.sin_family = AF_INET;
	srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// ソケットの生成（ストリーム型）
	srcSocket = socket(AF_INET, SOCK_STREAM, 0);
  	// ソケットのバインド
	bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));
  	// 接続の許可
	listen(srcSocket, 1);
}

void TcpServer::startService(){
	while(1){ //ループで回すことによって何度でもクライアントからつなぐことができる

		// 接続の受付け

    DebugPrint (TEXT("接続を待っています\nクライアントプログラムを動かしてください\n"));
		dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
	  DebugPrint (TEXT("接続を受けました\n"));

		while(1){
			//パケットの受信
			numrcv = recv(dstSocket, buffer, sizeof(char)*1024, 0);
			if(numrcv ==0 || numrcv ==-1 ){
				status = closesocket(dstSocket); break;
			}
//			printf("変換前 %s",buffer);


			for (int i=0; i< numrcv; i++){ // bufの中の小文字を大文字に変換
				//if(isalpha(buffer[i])) 
					buffer[i] = toupper(buffer[i]);
			}
			// パケットの送信
			send(dstSocket, buffer, sizeof(char)*1024, 0);
		  DebugPrint (TEXT("変換後の値を返却しました。\n"));

			//			printf("→ 変換後 %s \n",buffer);
		}
	}
}