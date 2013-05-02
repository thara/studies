#pragma once
#include "Service.h"
#include <windows.h>
#include <tchar.h>

//サービス名
#define SERVICE_NAME (TEXT("Demo_Service"))
//バッファサイズ
#define DEBUG_BUFF_SIZE (1024)



VOID DebugPrint (LPTSTR   szFormat, ... );
