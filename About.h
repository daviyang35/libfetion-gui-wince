#pragma once


// CAbout �Ի���

class CAbout : public CDialog
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAbout();

// �Ի�������
	enum { IDD = IDD_WMLF_ABOUT };

protected:
	CCommandBar m_dlgCommandBar;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};
