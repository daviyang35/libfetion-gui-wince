#pragma once


// CFindBuddyDlg �Ի���

class CFindBuddyDlg : public CDialog
{
	DECLARE_DYNAMIC(CFindBuddyDlg)

public:
	CFindBuddyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindBuddyDlg();

// �Ի�������
	enum { IDD = IDD_WMLF_FINDBUDDY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CCommandBar m_dlgCommandBar;

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnInitDialog();
};
