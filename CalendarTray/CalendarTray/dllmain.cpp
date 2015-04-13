// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <tchar.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define API_EXPORT __declspec(dllexport)

typedef LRESULT(CALLBACK *WNDPROC)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE	hMod;
HHOOK		hHook;
HWND		hWnd;
HWND		hWndTray;
WNDPROC		pfnWndProc;
BOOL		bOK;
HDC			hMemDCBkg;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
HWND FindWindow();

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	hMod = hModule;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR tcMsg[1024];

	switch (uMsg)
	{
	case	WM_LBUTTONDOWN:
		{
			OutputDebugString(_T("WM_LBUTTONDOWN"));
			HWND hWndCale = FindWindow(_T("#32770"), _T("CalendarMainWindow"));
			if (hWndCale)
			{
				/*COPYDATASTRUCT cds = { 0 };
				SendMessage(hWndCale, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
				OutputDebugString(_T("WM_COPYDATA"));*/
			}
			else
			{

				TCHAR szPath[2048] = { 0 };

				GetModuleFileName(hMod, szPath, 2047);
				PathRemoveFileSpec(szPath);

				_tcscat(szPath, _T("\\Calendar.exe"));

				OutputDebugString(szPath);

				STARTUPINFO si = { sizeof(si) };
				PROCESS_INFORMATION pi;
				if (CreateProcess(NULL, szPath, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) == TRUE)
				{
					CloseHandle(pi.hThread);
					CloseHandle(pi.hProcess);
				}
			}
			return 0;
		}
	case	WM_LBUTTONUP:		
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			RECT rcClient;
			POINT pt;

			GetClientRect(hWnd, &rcClient);			

			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hMemDC = CreateCompatibleDC(hdc);
			HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);
			
			HGDIOBJ hOldBitmap = SelectObject(hMemDC, hBitmap);			

			if(!bOK)
			{
				HWND hWndParent = GetParent(hWnd);

				POINT pos = {rcClient.left, rcClient.top};

				ClientToScreen(hWnd, &pos);
				ScreenToClient(hWndParent, &pos);

				SetWindowOrgEx(hdc, pos.x, pos.y, &pt);
				SendMessage(hWndParent, WM_PRINTCLIENT, (LPARAM)hdc, PRF_CLIENT | PRF_ERASEBKGND);
				SetWindowOrgEx(hdc, pt.x, pt.y, 0);

				if(!hMemDCBkg)
				{
					hMemDCBkg = CreateCompatibleDC(hdc);
				}

				HBITMAP hBitmapBkg = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);

				HGDIOBJ hOldBmp = SelectObject(hMemDCBkg, hBitmapBkg);

				BitBlt(hMemDCBkg, 0,0,rcClient.right, rcClient.bottom, hdc, 0, 0, SRCCOPY);

				SelectObject(hdc, hOldBmp);
				DeleteObject(hBitmapBkg);
				bOK = true;
				
			}			

			SetBkMode(hMemDC, TRANSPARENT);
			SetTextColor(hMemDC, RGB(255,255,255));			
			
			LOGFONT  font = {0};

			SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &font, 0);

			HDC hScreenDC = GetDC(NULL);

			double fPixelsX = GetDeviceCaps(hScreenDC, LOGPIXELSX);

			if(fPixelsX >= 110.0)
			{
				font.lfHeight = font.lfHeight / (fPixelsX / 96.0);
			}
			ReleaseDC(NULL, hScreenDC);

			HFONT hFont = CreateFontIndirect(&font);

			HGDIOBJ hOldFont = SelectObject(hMemDC, hFont);

			SetTextColor(hMemDC, 16777215);

			
			SYSTEMTIME st;
			GetLocalTime(&st);

			TCHAR szDate[32] = {0};
			TCHAR szTime[32] = {0};
			TCHAR szWeek[32] = {0};
			TCHAR* szWeeks[] = {_T("日"),_T("一"),_T("二"),_T("三"),_T("四"),_T("五"),_T("六")};

			BitBlt(hMemDC, 0,0,rcClient.right, rcClient.bottom, hMemDCBkg, 0, 0, SRCCOPY);

			if(rcClient.right > 70)
			{
				_stprintf(szWeek, _T("周%s %02d:%02d"), szWeeks[st.wDayOfWeek], st.wHour, st.wMinute);
				_stprintf(szDate, _T("%04d-%02d-%02d"), st.wYear, st.wMonth, st.wDay);

				RECT rcTime = { rcClient.left, rcClient.top + 18, rcClient.right, rcClient.bottom};

				DrawText(hMemDC, szWeek, _tcslen(szWeek), &rcClient, DT_CENTER);
				DrawText(hMemDC, szDate, _tcslen(szDate), &rcTime, DT_CENTER);
			}
			else
			{
				
				_stprintf(szTime, _T("%02d:%02d"), st.wHour, st.wMinute);
				_stprintf(szWeek, _T("周%s"), szWeeks[st.wDayOfWeek]);
				
				RECT rcTime = { rcClient.left, rcClient.top + 12, rcClient.right, rcClient.bottom};

				OSVERSIONINFO oi = { sizeof(oi) };
				GetVersionEx(&oi);

				if (oi.dwMajorVersion < 6)
				{
					rcClient.top += 5;
					rcTime.top += 5;
				}

				DrawText(hMemDC, szWeek, _tcslen(szWeek), &rcClient, DT_CENTER);
				DrawText(hMemDC, szTime, _tcslen(szTime), &rcTime, DT_CENTER);
			
			}

			BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hMemDC, 0, 0, SRCCOPY);
			

			SelectObject(hdc, hOldBitmap);
			SelectObject(hdc, hOldFont);
			DeleteObject(hBitmap);
			DeleteDC(hMemDC);			
			DeleteObject(hFont);

			EndPaint(hWnd, &ps);
		}
		return 0;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_TIMER:
		{			
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}
		return 0;
	default:
		if (uMsg == WM_WINDOWPOSCHANGED || uMsg == WM_THEMECHANGED)
		{
			bOK = false;
		}

		if(uMsg > WM_USER)
		{
			return pfnWndProc(hWnd, uMsg,wParam,lParam);
		}
		else
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	if (hWnd == NULL)
	{
		SYSTEM_INFO info = { 0 };
		GetNativeSystemInfo(&info);

		HINSTANCE hInst = NULL;
		if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		{
			LoadLibrary(_T("CalendarTray.dll"));
		}
		else
		{
			LoadLibrary(_T("CalendarTray64.dll"));
		}

		hWnd = FindWindow();	
	}

	if (GetWindowLongPtr(hWnd, GWLP_WNDPROC) != (LONG_PTR)WndProc)
	{
		pfnWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
		SetTimer(hWnd, 1, 100, NULL);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, _T("CalendarHookEvent"));
		SetEvent(hEvent);
		CloseHandle(hEvent);
	}



	return CallNextHookEx(hHook, nCode, wParam, lParam);	
}

HWND FindWindow()
{
	hWndTray = ::FindWindow(_T("Shell_TrayWnd"), NULL);

	if (hWndTray)
	{
		HWND hWndTrayNotify = ::FindWindowEx(hWndTray, NULL, _T("TrayNotifyWnd"), NULL);

		if (hWndTrayNotify)
		{
			return ::FindWindowEx(hWndTrayNotify, NULL, _T("TrayClockWClass"), NULL);
		}
	}

	return NULL;
}

void API_EXPORT InstallWindowsHook()
{
	hWnd = FindWindow();
	if (hWnd)
	{
		DWORD dwThreadID = GetWindowThreadProcessId(hWnd, NULL);
		hHook = SetWindowsHookExW(WH_GETMESSAGE, HookProc, hMod, dwThreadID);
		if (!hHook)
		{
			TCHAR tcMsg[1024];
			_stprintf(tcMsg, _T("error code: %d"), GetLastError());
			OutputDebugString(tcMsg);
		}
	}
	else
	{
		OutputDebugString(_T("InstallWindowsHook Failed"));
	}
}

void API_EXPORT UnInstallWindowsHook()
{
	if (hHook)
	{
		UnhookWindowsHookEx(hHook);
	}
}

