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

	//�T�[�r�X���C���������s�ۃt���O
	static BOOL g_bRun;
	//�T�[�r�X���s�����ۃt���O
	static BOOL g_bService;
	//�T�[�r�X�X�e�[�^�X�n���h��
	static SERVICE_STATUS_HANDLE g_hServiceStatus;
	//�T�[�o�[
	static TcpServer *srv;

	static int counter;

private: 


};