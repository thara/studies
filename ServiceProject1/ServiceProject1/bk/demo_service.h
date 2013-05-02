#pragma once

#include <windows.h>
#include <tchar.h>

DWORD WINAPI HandlerEx( 
	DWORD dwControl, 
	DWORD dwEventType, 
	PVOID pvEventData, 
	PVOID pvContext);
VOID WINAPI ServiceMain( DWORD dwArgc, PTSTR* pszArgv);
VOID DebugPrint (LPTSTR   szFormat, ... );
