﻿// About.cpp : 实现文件
//

#include "stdafx.h"
#include "WMLF.h"
#include "About.h"


// CAbout 对话框

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


// CAbout 消息处理程序

BOOL CAbout::OnInitDialog()
{
    CDialog::OnInitDialog();

	if (!m_dlgCommandBar.Create(this) ||
		!m_dlgCommandBar.InsertMenuBar(IDR_MENU_ABOUT))
	{
		TRACE0("未能创建 CommandBar\n");
		return FALSE;      // 未能创建
	}

    CString strAboutMsg;

	COleDateTime BuildDate;
	COleDateTime BuildTime;
	BuildDate.ParseDateTime(ConvertUtf8ToUtf16(__DATE__));
	BuildTime.ParseDateTime(ConvertUtf8ToUtf16(__TIME__));

	strAboutMsg.Format( 
_T("LibFetion For Windows Mobile\r\n\
V1.2.1 Build %s %s\r\n\r\n\
本程序基于LibFetion库编写，\r\n\
想了解更多请访问:\r\n\
www.libfetion.org.\r\n\
Copyright @ 2009-2010\r\n\
DDD(dedodong@163.com)\r\n\
All Rights Reserved.\r\n\r\n\
本程序由以下人员开发:\r\n\
\tgladyeti\r\n\
\tBabylon\r\n\
\tEric\r\n\
\tdaviyang35\r\n\
\tlionlee\r\n\
LibFetion库:\r\n\
\tDDD\r\n\
如有问题欢迎到论坛反馈。"),
BuildDate.Format(_T("%Y-%m-%d")),
BuildTime.Format(_T("%H:%M:%S"))
);
    
    ((CStatic*)this->GetDlgItem(IDC_STATIC_ABOUT))->SetWindowTextW(strAboutMsg);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

