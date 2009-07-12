#pragma once
#include "afxwin.h"


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
    void InitGroupItem(void);
    // ����ID��绰����
    CString m_strBuddyID;
    afx_msg void OnFbSetMobile();
    afx_msg void OnFbSetFxno();
    afx_msg void OnFbAdd();
    CComboBox m_cboGroup;
    CString m_strUserName;
    // ����ID���浽��������combobox�е�ÿһ��Index���Ӧ
    int m_iGroupIDs[25];
    // ��ʾ�������Ϣ
    CString m_strInfo;
    // �Է�����������
    CString m_strLocalName;
    afx_msg void OnStnClickedFbBtnFind();
};
