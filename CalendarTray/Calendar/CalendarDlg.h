
// CalendarDlg.h : header file
//

#pragma once
#include "explorer1.h"
#include "IDocHostUIHandlerImpl.h"

// CCalendarDlg dialog
class CCalendarDlg : public CDialogEx
{
// Construction
public:
	CCalendarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CALENDAR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);


	CExplorer m_web;
	afx_msg BOOL OnNcActivate(BOOL bActive);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_EVENTSINK_MAP()
	void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	IDocHostUIHandlerImpl*	m_pUIHandler;
};
