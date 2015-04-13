// CalendarInject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

void(*InstallWindowsHook)();
void(*UnInstallWindowsHook)();

int _tmain(int argc, _TCHAR* argv[])
{

	SYSTEM_INFO info = { 0 };
	GetNativeSystemInfo(&info);

	HINSTANCE hInst = NULL;
	if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
	{
		hInst = LoadLibrary(_T("CalendarTray.dll"));
	}
	else
	{
		hInst = LoadLibrary(_T("CalendarTray64.dll"));
	}

	if (hInst)
	{
		InstallWindowsHook = (void(*)())GetProcAddress(hInst, "InstallWindowsHook");
		UnInstallWindowsHook = (void(*)())GetProcAddress(hInst, "UnInstallWindowsHook");
		if (!InstallWindowsHook || !UnInstallWindowsHook)
		{
			_tprintf(_T("GetProcAddress failed"));
			return -2;
		}
	}
	else
	{
		_tprintf(_T("Load CalendarTray64.dll failed. code:%d"), GetLastError());
		return -3;
	}


	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, _T("CalendarHookEvent"));
	
	InstallWindowsHook();
	WaitForSingleObject(hEvent, 2000);
	FreeLibrary(hInst);

	return 0;
}

