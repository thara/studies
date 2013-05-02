#include "Service.h"
#include "demo_service.h"
#include <stdarg.h>
#include <wtypes.h>


/*
	静的メンバ変数初期化
*/
	//サービスメイン部分実行可否フラグ
	BOOL Service::g_bRun = TRUE;
	//サービス実行存続可否フラグ
	BOOL Service::g_bService = TRUE;
	//サービスステータスハンドル
	SERVICE_STATUS_HANDLE Service::g_hServiceStatus = NULL;
	//サーバー
	TcpServer *Service::srv = new TcpServer();


Service::Service(void)
{
}


Service::~Service(void)
{
}


////////////////////////////////////////////////////////////////////////////////

//制御子（ここがスタート以外の制御を行う。STOP,PAUSE,CONTINUE,,,etc）
DWORD WINAPI Service::HandlerEx ( 
	DWORD dwControl, 
	DWORD dwEventType, 
	LPVOID lpEventData, 
	LPVOID lpContext ) {

     SERVICE_STATUS ss;
     /*
		typedef unsigned long       DWORD;
		typedef struct _SERVICE_STATUS {
			DWORD   dwServiceType;
			DWORD   dwCurrentState;
			DWORD   dwControlsAccepted;
			DWORD   dwWin32ExitCode;
			DWORD   dwServiceSpecificExitCode;
			DWORD   dwCheckPoint;
			DWORD   dwWaitHint;
		} SERVICE_STATUS, *LPSERVICE_STATUS;
		*/
		 
		 BOOL bRet;
     //typedef int                 BOOL;

     //サービスの初期化
		 // Initialize Variables for Service Control
     ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
     ss.dwWin32ExitCode = NO_ERROR;
     ss.dwServiceSpecificExitCode = 0;
     ss.dwCheckPoint = 1;
     ss.dwWaitHint = 3000;
     ss.dwControlsAccepted = SERVICE_ACCEPT_STOP;

     switch(dwControl) {
     /*
//
// Controls
//
#define SERVICE_CONTROL_STOP                   0x00000001
#define SERVICE_CONTROL_PAUSE                  0x00000002
#define SERVICE_CONTROL_CONTINUE               0x00000003
#define SERVICE_CONTROL_INTERROGATE            0x00000004
#define SERVICE_CONTROL_SHUTDOWN               0x00000005
#define SERVICE_CONTROL_PARAMCHANGE            0x00000006
#define SERVICE_CONTROL_NETBINDADD             0x00000007
#define SERVICE_CONTROL_NETBINDREMOVE          0x00000008
#define SERVICE_CONTROL_NETBINDENABLE          0x00000009
#define SERVICE_CONTROL_NETBINDDISABLE         0x0000000A
#define SERVICE_CONTROL_DEVICEEVENT            0x0000000B
#define SERVICE_CONTROL_HARDWAREPROFILECHANGE  0x0000000C
#define SERVICE_CONTROL_POWEREVENT             0x0000000D
#define SERVICE_CONTROL_SESSIONCHANGE          0x0000000E
#define SERVICE_CONTROL_PRESHUTDOWN            0x0000000F
#define SERVICE_CONTROL_TIMECHANGE             0x00000010
#define SERVICE_CONTROL_TRIGGEREVENT           0x00000020
		 */
		 
		 case SERVICE_CONTROL_STOP:
					//ストップ時イベント

          DebugPrint (TEXT("SERVICE_CONTROL_STOP\n"));

          // Set STOP_PENDING status.
          ss.dwCurrentState = SERVICE_STOP_PENDING;
               
          bRet = SetServiceStatus (g_hServiceStatus, &ss);
          
          if (!bRet) {
               DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
               break;
          }

          // SERVICE SPECIFIC STOPPING CODE HERE.
          // ...
          // ...
          //サービスを終了させる
          g_bService = FALSE;
					srv->~TcpServer();
					Sleep (3 * 1000);


          // Set STOPPED status.
          ss.dwCurrentState = SERVICE_STOPPED;
          ss.dwCheckPoint = 0;
          ss.dwWaitHint = 0;
          
          bRet = SetServiceStatus (g_hServiceStatus, &ss);
                    
          if (!bRet) {
               DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
               break;
          }

          break;

     case SERVICE_CONTROL_PAUSE:
					//一時停止

					DebugPrint (TEXT("SERVICE_CONTROL_PAUSE\n"));

          // Set PAUSE_PENDING status.
          ss.dwCurrentState = SERVICE_PAUSE_PENDING;
                         
          bRet = SetServiceStatus (g_hServiceStatus, &ss);
                    
          if (!bRet) {
               DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
               break;
          }

          // APPLICATION SPECIFIC PAUSE_PENDING CODE HERE.
          // ...
          // ...
					//サービスを一時停止する 
          g_bRun = FALSE;

          // Set PAUSE_PENDING status.
          ss.dwCurrentState = SERVICE_PAUSED;
          ss.dwCheckPoint = 0;
          ss.dwWaitHint = 0;
          ss.dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;
                                   
          bRet = SetServiceStatus (g_hServiceStatus, &ss);
                              
          if (!bRet) {
               DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
               break;
          }
          
          break;
          
     case SERVICE_CONTROL_CONTINUE:
					//コンティニュー時（一時停止から復帰した際）

          DebugPrint (TEXT("SERVICE_CONTROL_CONTINUE\n"));

          // Set PAUSE_PENDING status.
          ss.dwCurrentState = SERVICE_START_PENDING;
                                   
          bRet = SetServiceStatus (g_hServiceStatus, &ss);
                              
          if (!bRet) {
               DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
               break;
          }
          
          // APPLICATION SPECIFIC START_PENDING CODE HERE.
          // ...
          // ...
          //サービス一時停止からの復帰          
          g_bRun = TRUE;
          
          // Set RUNNING status.
          ss.dwCurrentState = SERVICE_RUNNING;
          ss.dwCheckPoint = 0;
          ss.dwWaitHint = 0;
          ss.dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;
                                             
          bRet = SetServiceStatus (g_hServiceStatus, &ss);
                                        
          if (!bRet) {
               DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
               break;
          }
          
          break;
     default:

          //STOP,CONTINUE,PAUSE以外のハンドルが行われた場合
					return ERROR_CALL_NOT_IMPLEMENTED;

     }

     return NO_ERROR;
}


///////////////////////////////////////////////////////////////////////////////


//サービスメイン
//ここが一番最初に動いて準備、ループを行う
VOID WINAPI Service::ServiceMain(DWORD dwArgc, PTSTR* pszArgv) {
			
		BOOL bRet;
    SERVICE_STATUS ss;

     //初期化
		 // Initialize Variables for Service Control
     ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
     ss.dwWin32ExitCode = NO_ERROR;
     ss.dwServiceSpecificExitCode = 0;
     ss.dwCheckPoint = 1;
     ss.dwWaitHint = 1000;
     ss.dwControlsAccepted = SERVICE_ACCEPT_STOP;

     
		 //制御用ハンドラーの登録
		 // Register Service Control Handler
     g_hServiceStatus = 
			 RegisterServiceCtrlHandlerEx (SERVICE_NAME, Service::HandlerEx, NULL);
		 /*
		  WINAPI
RegisterServiceCtrlHandlerExA(
    _In_    LPCSTR                    lpServiceName,
    _In_    __callback
            LPHANDLER_FUNCTION_EX       lpHandlerProc,
    _In_opt_ LPVOID                     lpContext
    );
_Must_inspect_result_

		 */


     if(0 == g_hServiceStatus) {
          DebugPrint (
               TEXT("RegisterServiceCtrlHandler failed. %u\n"), 
               GetLastError());
          return;
     }

     // Entering Starting Service.
     DebugPrint (TEXT("SERVICE_START_PENDING...\n"));
     
     ss.dwCurrentState = SERVICE_START_PENDING;
     
     bRet = SetServiceStatus (g_hServiceStatus, &ss);

     if (!bRet) {
          DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
          return;
     }

     // APPLICATION SPECIFIC INITIALIZATION CODE
     // ...
     // ...
     
     // Finish Initializing.
     DebugPrint (TEXT("SERVICE_RUNNING.\n"));
     
     ss.dwCurrentState = SERVICE_RUNNING;
     ss.dwCheckPoint = 0;
     ss.dwWaitHint = 0;
     ss.dwControlsAccepted = 
          SERVICE_ACCEPT_PAUSE_CONTINUE |
          SERVICE_ACCEPT_STOP;
          
     bRet = SetServiceStatus (g_hServiceStatus, &ss);
          
     if (!bRet) {
          DebugPrint (TEXT("SetServiceStatus failed. %u\n"), GetLastError());
          return;
     }

     //
     // Service Main Code.
     //
     //srv = new TcpServer();

		 boolean srvFlg = true;

		 while(g_bService) {

          if(g_bRun) {
               DebugPrint (TEXT("%s is running.\n"), SERVICE_NAME);
						if(srvFlg) {
							srv->startService();
							srvFlg = false;	
						}
          }

          Sleep(2 * 1000);
     }

     DebugPrint (TEXT("END OF ServiceMain\n"));
     
}


///////////////////////////////////////////////////////////////////////////////
