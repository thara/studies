#pragma once
#include "Service.h"
#include <windows.h>
#include <tchar.h>

//�T�[�r�X��
#define SERVICE_NAME (TEXT("Demo_Service"))
//�o�b�t�@�T�C�Y
#define DEBUG_BUFF_SIZE (1024)



VOID DebugPrint (LPTSTR   szFormat, ... );
