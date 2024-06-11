#include "pch.h"
#include "CListenSocket.h"
#include "CClientSocket.h"
#include "CQQChatServerDlg.h"


CListenSocket::CListenSocket()
{
    // Implementation of the constructor
    // Initialization code here
}

CListenSocket::~CListenSocket()
{
    // Implementation of the constructor
    // Initialization code here
}

void CListenSocket::OnAccept(int nErrorCode) {

    CClientSocket *pSocket = new CClientSocket;
    if (Accept(*pSocket))
    {
        //获取客户端的ip地址和端口号
        CString strIPAddress;
        UINT uPort;

        pSocket->GetPeerName(strIPAddress, uPort);

        //将IP地址和端口号插入列表
        CQQChatServerDlg* pMainDlg = (CQQChatServerDlg*)AfxGetMainWnd();
        if (pMainDlg != nullptr)
        {
            pMainDlg->m_list.InsertItem(0, strIPAddress);
            CString str;
            str.Format(L"%d", uPort);
            pMainDlg->m_list.SetItemText(0, 1, str);
        }
    }

    CSocket::OnAccept(nErrorCode); // Call the base class implementation
}