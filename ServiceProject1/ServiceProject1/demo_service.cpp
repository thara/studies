//
// Demo Service
//
#include "demo_service.h"
#include "Service.h"

#include <assert.h>
#include <stdio.h>
//呼び出しメイン
//StartServiceCtrlDispatcherにサービス登録したテーブルを放り投げる
VOID main() {

   //BOOL bRet;
   //bRet = StartServiceCtrlDispatcher (ServiceTable);
	//assert(bRet);

	//Service *srv = new Service();
	//VOID (WINAPI *hoge)(DWORD dwArgc, PTSTR* pszArgv) =  &Service::ServiceMain;
	//クラスのメンバ関数ポインタはHogeClass::*となってしまい
	//通常の関数ポインタとは型が異なる。

	//void (CSample::*pFunc)() = &CSample::func;


	//サービス登録用テーブル準備
	SERVICE_TABLE_ENTRY ServiceTable[] = {
          { SERVICE_NAME, &Service::ServiceMain },
          { NULL, NULL }
	};
	/*
	typedef struct _SERVICE_TABLE_ENTRYA {
    LPSTR                       lpServiceName;
    LPSERVICE_MAIN_FUNCTIONA    lpServiceProc;
}SERVICE_TABLE_ENTRYA, *LPSERVICE_TABLE_ENTRYA;

typedef VOID (WINAPI *LPSERVICE_MAIN_FUNCTIONA)(
    DWORD   dwNumServicesArgs,
    LPSTR   *lpServiceArgVectors
    );



	*/


	//Dispatcherの戻り値で警告を出す
	assert(StartServiceCtrlDispatcher(ServiceTable));

}



//デバッグ出力用関数
VOID DebugPrint (LPTSTR   szFormat, ... ) {

     TCHAR    szBuffer[DEBUG_BUFF_SIZE + 1];
     INT     nWritten;
     va_list args;

     ::ZeroMemory(szBuffer, sizeof(szBuffer));

     // Format error message like printf()
     
     va_start( args, szFormat );

		 nWritten = _vsnprintf_s( szBuffer, DEBUG_BUFF_SIZE, szFormat, args );

     va_end( args );

     // Output debug string

     ::OutputDebugString( szBuffer );

     
}