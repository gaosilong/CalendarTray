
// Calendar.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCalendarApp:
// See Calendar.cpp for the implementation of this class
//

class CCalendarApp : public CWinApp
{
public:
	CCalendarApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCalendarApp theApp;