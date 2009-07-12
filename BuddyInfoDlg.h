#pragma once
#include "afxwin.h"


// CBuddyInfoDlg �Ի���

class CBuddyInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBuddyInfoDlg)

public:
	CBuddyInfoDlg(long lAccountID = 0, CWnd* pParent = NULL);   // ��׼���캯��
	
	virtual ~CBuddyInfoDlg();

// �Ի�������
	enum { IDD = IDD_WMLF_BUDDYINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CCommandBar m_dlgCommandBar;

	DECLARE_MESSAGE_MAP()
public:


    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    void CBuddyInfoDlg::InitScrollInfo();

	const Fetion_Account *m_account;
    // ��������
    CString m_strShowName;
    // ������
    int m_iGroupID;
    // ���ź���
    long m_lAccountID;
    // �ǳ�
    CString m_strNickName;
    CString m_strName;
    CString m_strSex;
    CString m_strProv;
    CString m_strCity;
    // ǩ��
    CString m_strSign;
    void InitGroupItem(void);
    CComboBox m_cboGroup;
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    // ����ID���浽��������combobox�е�ÿһ��Index���Ӧ
    int m_iGroupIDs[25];
    afx_msg void OnOk();
};
