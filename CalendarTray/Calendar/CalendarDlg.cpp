
// CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calendar.h"
#include "CalendarDlg.h"
#include "afxdialogex.h"
#include   <exdispid.h> 
#include   <mshtmhst.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalendarDlg dialog



CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalendarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
}

BEGIN_MESSAGE_MAP(CCalendarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_COPYDATA()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetWindowText(_T("CalendarMainWindow"));

	TCHAR szPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szPath, MAX_PATH);
	PathRemoveFileSpec(szPath);
	
	CString strPath = _T("file:///");
	strPath = strPath + szPath + _T("\\rili.html");

	m_pUIHandler = new IDocHostUIHandlerImpl;
	m_web.Navigate(_T("about:blank"), NULL, NULL, NULL, NULL);


	m_web.Navigate(strPath, NULL, NULL, NULL, NULL);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);

	int nHeight = cy - rt.Height();

	CRect rect;
	GetWindowRect(&rect);

	MoveWindow(cx - rect.Width() - 2, cy - nHeight - rect.Height() - 2, rect.Width(), rect.Height(), FALSE);

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	AnimateWindow(200, AW_CENTER);
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalendarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalendarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalendarDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: Add your message handler code here
}


BOOL CCalendarDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


void CCalendarDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	if (nState == WA_INACTIVE)
	{
		OnOK();
	}
	// TODO: Add your message handler code here
}
BEGIN_EVENTSINK_MAP(CCalendarDlg, CDialogEx)
	ON_EVENT(CCalendarDlg, IDC_EXPLORER1, 259, CCalendarDlg::DocumentComplete, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()


void CCalendarDlg::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
	CComQIPtr<ICustomDoc, &IID_ICustomDoc> pCustomDoc(m_web.get_Document());
	if (pCustomDoc)
	{
		pCustomDoc->SetUIHandler(m_pUIHandler);
	}
	// TODO: Add your message handler code here
}
