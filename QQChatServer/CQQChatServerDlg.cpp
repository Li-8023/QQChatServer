
// QQChatServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "QQChatServer.h"
#include "CQQChatServerDlg.h"
#include "afxdialogex.h"
#include "CListenSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQChatServerDlg dialog



CQQChatServerDlg::CQQChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QQCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListenSocket = NULL;
}

void CQQChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CQQChatServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CQQChatServerDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CQQChatServerDlg::OnBnClickedBtnClose)
END_MESSAGE_MAP()


// CQQChatServerDlg message handlers

BOOL CQQChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(FALSE);

	m_list.InsertColumn(0, L"IP Address", LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, L"Port", LVCFMT_LEFT, 100);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQQChatServerDlg::OnPaint()
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
HCURSOR CQQChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//开启服务器
void CQQChatServerDlg::OnBnClickedBtnStart()
{
	m_pListenSocket = new CListenSocket;

	//创建套接字(Socket)
	//10086: port number
	//TCP协议
	if (FALSE == m_pListenSocket->Create(10086, SOCK_STREAM)) {
		MessageBox(L"创建套接字失败");
		return;
	}

	//将套接字设置为监听模式
	//盯着10086，看别人有没有人连接他
	if (FALSE == m_pListenSocket->Listen()) {
		MessageBox(L"监听失败");
		return;
	}

	//修改按钮状态
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(TRUE);
	
}


void CQQChatServerDlg::OnBnClickedBtnClose()
{

	if (m_pListenSocket) {
		delete m_pListenSocket; //释放内存
		m_pListenSocket = NULL;
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(FALSE);
	}
}
