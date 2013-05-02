#pragma once
#include "TcpServer.h"


class Service
{
public:
	Service(void);
	~Service(void);
	static DWORD WINAPI HandlerEx( 
		DWORD dwControl, 
		DWORD dwEventType, 
		PVOID pvEventData, 
		PVOID pvContext);
	static VOID WINAPI ServiceMain( DWORD dwArgc, PTSTR* pszArgv);

	//サービスメイン部分実行可否フラグ
	static BOOL g_bRun;
	//サービス実行存続可否フラグ
	static BOOL g_bService;
	//サービスステータスハンドル
	static SERVICE_STATUS_HANDLE g_hServiceStatus;
	//サーバー
	static TcpServer *srv;

	static int counter;

private: 


};