
/***************************************************************************
 *   Copyright (C) 2008 by DDD                                          *
 *   dedodong@163.com                                                     *
 *                                                                         *
 ***************************************************************************/
// WMLFDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define FX_LOGINSTATE_MSG WM_USER+1 

// CLoginDlg �Ի���
class CLoginDlg : public CDialog
{
// ����
public:
	CLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WMLF_DIALOG };

#ifdef WIN32_PLATFORM_WFSP
protected:  // �ؼ���Ƕ���Ա
	CCommandBar m_dlgCommandBar;
#endif // WIN32_PLATFORM_WFSP

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	// ����ID
	CString m_fetion_id;
public:
	// ���ŵ�¼����
	CString m_passwd;

	//save fetion server address
	CString m_server_addr;

public:
	afx_msg void OnBnClickedLogin();
public:
	// ���ŵ�¼״̬
	CString m_login_state;
public:
	// ���ŵ�¼��־
	BOOL m_LoginFlag;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedRemAccount();
public:
	CButton RemAccount;
public:
	afx_msg void OnLogin();
public:
	afx_msg void OnIDM_Cancel();
protected:
	virtual void OnCancel();
};
