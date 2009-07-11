
/***************************************************************************
 *   Copyright (C) 2008 by DDD                                          *
 *   dedodong@163.com                                                     *
 *                                                                         *
 ***************************************************************************/
#pragma once
#include "afxcmn.h"
#include "MessageLog.h"

class CLoginDlg;
class BuddyOpt;
class FxMsgDlg;

// FxMainWin �Ի���
class FxMainWin : public CDialog
{
	DECLARE_DYNAMIC(FxMainWin)

public:
	FxMainWin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FxMainWin();

//#ifdef WIN32_PLATFORM_WFSP
protected:  // �ؼ���Ƕ���Ա
	CCommandBar m_dlgCommandBar;
//#endif // WIN32_PLATFORM_WFSP

	void do_login();
// �Ի�������
	enum { IDD = IDD_WMLF_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
#if defined(_DEVICE_RESOLUTION_AWARE)// && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT nType, int cx, int cy);
#endif
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:

	//login window
	CLoginDlg *loginDlg;
	BuddyOpt *m_BuddyOpt;

public:
	CTreeCtrl view;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnTvnKeydownTreeBuddy(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnClose();
protected:
	BOOL handleFx_Sys_Event(int message, WPARAM wParam, LPARAM lParam);
public:
	BOOL showBuddyMenu(CPoint point);
	BOOL showBuddyMenu(HTREEITEM hItem);
public:
    BOOL FxMainWin::showMsgDlg();
	BOOL showMsgDlg(CPoint point);
	BOOL showMsgDlg(HTREEITEM hItem);
public:
	CList<HTREEITEM> filker;
	CList<int> timeOutMsgVector;
	CList<TMPMSG_Info*> tmpMsg;
public:
	//��ǰ����Ի���
	FxMsgDlg* m_currentMsgDlg;
	//��ǰ����Item
	HTREEITEM m_currentItem;
public:
	void relogin_fetion();
	void update_account_info();
	void relogin_ok();
	bool hand_SystemNetErr(int errcode);
	void filker_newmsg();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSendMsg();
public:
	void handle_relogin_Event(int message, WPARAM wParam, LPARAM lParam);
	void hand_MsgSend_Event(int message, int fx_msg, long who);
	void handle_sendmsg(int msgflag, int fx_msg, long account_id);
	void addNewMessage(long account_id, CString newmsg = _T(""));
    BOOL SetUserOnlineState(int iState);
public:
	BOOL m_isLoginOK;
    // �û��ǳ�
    CString m_strNickName;
    // �û�ǩ��
    CString m_strSign;
    afx_msg void OnStnClickedBtnAdd();
    // �����¼����
    CMessageLog m_MessageLog;
    // ��Ϣ��ʾ
    void NotifyUser(int EventType);
    // �Ƿ����յ���Ϣʱ������
    bool m_bVibrate;

    // �Ƿ����յ���Ϣʱ����
    bool m_bSilence;
    afx_msg void OnMainSetVibr();
    afx_msg void OnMainSetSilence();
    afx_msg void OnUpdateMainSetSilence(CCmdUI *pCmdUI);
    afx_msg void OnUpdateMainSetVibr(CCmdUI *pCmdUI);
    // ��������·��
    CString m_strStartupPath;
    // ��ȡ����·��
    CString GetStartupPath(void);
    // ��ǰ��¼�û���ID
    long m_lAccountID;
};
