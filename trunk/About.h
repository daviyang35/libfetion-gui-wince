﻿#pragma once


// CAbout 对话框

class CAbout : public CDialog
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAbout();

// 对话框数据
	enum { IDD = IDD_WMLF_ABOUT };

protected:
	CCommandBar m_dlgCommandBar;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};
