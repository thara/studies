//
// Demo Service
//
#include "demo_service.h"
#include "Service.h"

#include <assert.h>
#include <stdio.h>
//�Ăяo�����C��
//StartServiceCtrlDispatcher�ɃT�[�r�X�o�^�����e�[�u������蓊����
VOID main() {

   //BOOL bRet;
   //bRet = StartServiceCtrlDispatcher (ServiceTable);
	//assert(bRet);

	//Service *srv = new Service();
	//VOID (WINAPI *hoge)(DWORD dwArgc, PTSTR* pszArgv) =  &Service::ServiceMain;
	//�N���X�̃����o�֐��|�C���^��HogeClass::*�ƂȂ��Ă��܂�
	//�ʏ�̊֐��|�C���^�Ƃ͌^���قȂ�B

	//void (CSample::*pFunc)() = &CSample::func;


	//�T�[�r�X�o�^�p�e�[�u������
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


	//Dispatcher�̖߂�l�Ōx�����o��
	assert(StartServiceCtrlDispatcher(ServiceTable));

}



//�f�o�b�O�o�͗p�֐�
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