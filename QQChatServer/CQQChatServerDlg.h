
// QQChatServerDlg.h : header file
//

#pragma once
#include "resource.h"
#include "afxwin.h"

class CListenSocket;

// CQQChatServerDlg dialog
class CQQChatServerDlg : public CDialogEx
{
// Construction
public:
	CQQChatServerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQCHATSERVER_DIALOG };
#endif

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
	CListenSocket* m_pListenSocket;
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnClose();
	CListCtrl m_list;
};
