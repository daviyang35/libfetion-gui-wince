// About.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WMLF.h"
#include "About.h"


// CAbout �Ի���

IMPLEMENT_DYNAMIC(CAbout, CDialog)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
//    ON_WM_SIZE()
END_MESSAGE_MAP()


// CAbout ��Ϣ�������

BOOL CAbout::OnInitDialog()
{
    CDialog::OnInitDialog();

	if (!m_dlgCommandBar.Create(this) ||
		!m_dlgCommandBar.InsertMenuBar(IDR_MENU_ABOUT))
	{
		TRACE0("δ�ܴ��� CommandBar\n");
		return FALSE;      // δ�ܴ���
	}

    CString strAboutMsg = 
_T("����LibFetion WM��(20090713alpha)\r\n\r\n\
���������LibFetion���д���˽���������\r\n\
www.libfetion.cn.\r\n\
Copyright @ 2009 DDD(dedodong@163.com) \r\n\
All Rights Reserved.\r\n\r\n\
Windows Mobile �汾��������Ա����:\r\n\
����:\t\tDDD\r\n\
����&&Э��:\tdaviyang35\r\n\
����&&UI:\tBabylon\r\n\
����&&SP��UI:\tEric\r\n\
�������⻶ӭ����̳������");
    
    ((CStatic*)this->GetDlgItem(IDC_STATIC_ABOUT))->SetWindowTextW(strAboutMsg);
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

