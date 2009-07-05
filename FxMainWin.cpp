/***************************************************************************
 *   Copyright (C) 2008 by DDD                                          *
 *   dedodong@163.com                                                     *
 *                                                                         *
 ***************************************************************************/

// FxMainWin.cpp : 实现文件
#include "stdafx.h"
#include "WMLF.h"
#include "FxMainWin.h"
#include "LoginDlg.h"
#include "FxMsgDlg.h"
#include "FxBuddy.h"

#define TIMER_NEWMSG  15
#define TIMER_RELOGIN 20
#define TIMER_UPDATE_ACCOUNTINFO 25

void  Sys_EventListener (int message, WPARAM wParam, LPARAM lParam, void* args)
{
	if(!args)
		return;
	FxMainWin * mainWind = (FxMainWin *) args;
	//::SendMessage(mainWind->m_hWnd, message + WM_USER, wParam, lParam);
	::PostMessage(mainWind->m_hWnd, message + WM_USER, wParam, lParam);
}

BOOL FxMainWin::handleFx_Sys_Event(int message, WPARAM wParam, LPARAM lParam)
{
	if (message < WM_USER)
		return FALSE;

	switch(message - WM_USER)
	{
	case FX_CURRENT_VERSION:
		//emit signal_Current_Version((int)wParam);
		return TRUE;
	case FX_ADDACCOUNT_APP:
		//emit signal_AddAccountApp((char*)(lParam), (char*)wParam);
		return TRUE;
	case FX_MOVE_GROUP_OK:
		//emit signal_MoveGroup(qlonglong(lParam), (int)wParam);
		return TRUE;
	case FX_NEW_MESSAGE:
		addNewMessage(long(lParam));
		return TRUE;
	case FX_NEW_QUN_MESSAGE:
		//emit signal_NewQunMsg(qlonglong(lParam));
		return TRUE;
	case FX_SET_STATE_OK:
		//emit signal_set_state((int)wParam);
		return TRUE;

	case FX_STATUS_OFFLINE: 
	case FX_STATUS_ONLINE:
	case FX_STATUS_BUSY: 
	case FX_STATUS_AWAY: 
	case FX_STATUS_MEETING:
	case FX_STATUS_PHONE:  
	case FX_STATUS_DINNER: 
	case FX_STATUS_EXTENDED_AWAY:
	case FX_STATUS_NUM_PRIMITIVES:
	case FX_ACCOUNT_UPDATA_OK:
	case FX_REMOVE_BLACKLIST_OK:
	case FX_ADD_BLACKLIST_OK:
	case FX_STATUS_SMSEXTENED:
		this->m_BuddyOpt->updateAccountInfo(lParam);
		return TRUE;

	case FX_SET_REFUSE_SMS_DAY_OK:
		//emit signal_UpdateSmsDay((wParam));
		return TRUE;

	case FX_SYS_ERR_NETWORK:
		hand_SystemNetErr( wParam);
		return TRUE;

	case FX_SYS_DEREGISTERED:
		AfxMessageBox(_T("您已经在其它地方登录，程序将退出"));
		::exit(0); //fixed: no release the res of this app...
		return TRUE;

	case FX_DIA_SEND_OK: 
	case FX_DIA_SEND_FAIL: 
	case FX_DIA_SEND_TIMEOUT: 
	case FX_SMS_OK: 
	case FX_SMS_FAIL: 
	case FX_SMS_FAIL_LIMIT: 
	case FX_SMS_TIMEOUT: 
	case FX_QUN_SEND_OK: 
	case FX_QUN_SEND_FAIL: 
	case FX_QUN_SEND_TIMEOUT: 
	case FX_QUN_SMS_OK: 
	case FX_QUN_SMS_FAIL: 
	case FX_QUN_SMS_FAIL_LIMIT: 
	case FX_QUN_SMS_TIMEOUT: 
		hand_MsgSend_Event( message - WM_USER, wParam, (long)lParam);
		return TRUE;

	case FX_ADD_BUDDY_OK:
		//emit signal_add_buddy( message, wParam, (qlonglong)lParam);
		return TRUE;

	case FX_RENAME_GROUP_OK:
		//emit signal_reName_group( message, wParam, (qlonglong)lParam);
		return TRUE;
	case FX_SET_BUDDY_INFO_OK:
		//emit signal_reName_buddy( message, wParam, (qlonglong)lParam);
		return TRUE;
	case FX_ADD_GROUP_OK:
		//emit signal_add_group( message, wParam, (qlonglong)lParam);
		return TRUE;
	case FX_DEL_GROUP_OK:
		//emit signal_del_group( message, wParam, (qlonglong)lParam);
		return TRUE;
	case FX_DEL_BUDDY_OK:
		//emit signal_del_buddy( message, wParam, (qlonglong)lParam);
		return TRUE;

	case FX_ADD_GROUP_FAIL:
	case FX_DEL_GROUP_FAIL:
	case FX_SET_BUDDY_INFO_FAIL:
	case FX_RENAME_GROUP_FAIL:  //ignored this message
		if(wParam)
			free((char*)(int)wParam);
		return TRUE;

	case FX_SET_NICKNAME_OK:
		//emit signal_set_nickname_ok();
		return TRUE;

#if 0 //follow message is ignored
	case FX_MOVE_GROUP_FAIL:
	case FX_REMOVE_BLACKLIST_FAIL:
	case FX_ADD_BLACKLIST_FAIL:
	case FX_REMOVE_BLACKLIST_TIMEOUT:
	case FX_ADD_BLACKLIST_TIMEOUT:
	case FX_RENAME_GROUP_TIMEOUT:
	case FX_SET_BUDDY_INFO_TIMEOUT:
	case FX_SET_REFUSE_SMS_DAY_FAIL:
#endif

		//for relogin message. note: not for login
	case FX_LOGIN_URI_ERROR:
	case FX_LOGIN_FAIL:
	case FX_LOGIN_NETWORK_ERROR:
	case FX_LOGIN_UNKOWN_ERROR :   
	case FX_LOGIN_UNKOWN_USR:
	case FX_LOGIN_GP_FAIL:
		relogin_fetion();
		break;
	case FX_LOGIN_OK :
		KillTimer(TIMER_RELOGIN);
		relogin_ok();
		break;
//for relogin message. note: not for login

	default:
		break;
	}
	return FALSE;
}

// FxMainWin 对话框

IMPLEMENT_DYNAMIC(FxMainWin, CDialog)

FxMainWin::FxMainWin(CWnd* pParent /*=NULL*/)
	: CDialog(FxMainWin::IDD, pParent)
	, loginDlg(NULL)
	, m_BuddyOpt(NULL)
	, m_currentMsgDlg(NULL)
	, m_currentItem(NULL)
	, m_isLoginOK(FALSE)
{

}

FxMainWin::~FxMainWin()
{
}

void FxMainWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_BUDDY, view);
}


BEGIN_MESSAGE_MAP(FxMainWin, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

#ifdef WIN32_PLATFORM_WFSP
WNDPROC prevProc;  //取得原窗口过程函数指针
CTreeCtrl *g_cTree;  //CTreeCtrl指针，用于获取Dlg中的控件

LRESULT CALLBACK MyTreeProc(
							HWND hwnd,      // handle to window
							UINT uMsg,      // message identifier
							WPARAM wParam,  // first message parameter
							LPARAM lParam   // second message parameter
							)
{
		if(WM_GETDLGCODE == uMsg)
	{
		return   DLGC_WANTMESSAGE; 
	}
	else if(WM_KEYDOWN == uMsg &&  VK_RETURN == wParam)  //确认键按下
	{
		//展开选中节点
		HTREEITEM hItem = g_cTree->GetSelectedItem();
		if ((hItem != NULL) && g_cTree->ItemHasChildren(hItem))
		{
			g_cTree->Expand(hItem, TVE_TOGGLE);
			/*
			if ((g_cTree->GetItemState(hItem, TVIS_EXPANDED) & TVIS_EXPANDED) == FALSE) //未展开
			{
				g_cTree->Expand(hItem, TVE_EXPAND);
				g_cTree->EnsureVisible(hItem);
			}
			else  //展开
			{
				g_cTree->Expand(hItem, TVE_COLLAPSE);
			}
			*/
		}

		return 1;
	}
	else
	{
		return prevProc(hwnd,uMsg,wParam,lParam);
	}
}
#endif // WIN32_PLATFORM_WFSP

// FxMainWin 消息处理程序

BOOL FxMainWin::OnInitDialog()
{
	do_login();
	CDialog::OnInitDialog();
	
	//set the fetion system msg call back function
	fx_set_system_msg_cb (Sys_EventListener, this);
#ifdef WIN32_PLATFORM_WFSP
	g_cTree = &view;  
	prevProc=(WNDPROC)SetWindowLong(view.m_hWnd,GWL_WNDPROC,(LONG)MyTreeProc);
#endif // WIN32_PLATFORM_WFSP

	m_BuddyOpt = new BuddyOpt(&view);
	
#ifdef WIN32_PLATFORM_WFSP

	if (!m_dlgCommandBar.Create(this) ||
		!m_dlgCommandBar.InsertMenuBar(IDR_MAIN_MENU))
	{
		TRACE0("未能创建 CommandBar\n");
		return FALSE;      // 未能创建
	}
#endif // WIN32_PLATFORM_WFSP
	// TODO: 在此添加额外的初始化代码

	SetTimer(TIMER_UPDATE_ACCOUNTINFO, 1000*3, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
}

void FxMainWin::do_login()
{
	loginDlg = new CLoginDlg;
	loginDlg->DoModal();

	//if login false, will exit the application
	if (loginDlg->m_LoginFlag != TRUE)
	{
		m_isLoginOK = FALSE;
		//AfxMessageBox(_T("will quit"));
		fx_terminate();
		::exit(0);
	} else {
		m_isLoginOK = TRUE;
	}

}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void FxMainWin::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	DRA::RelayoutDialog(
		AfxGetInstanceHandle(), 
		this->m_hWnd, 
		DRA::GetDisplayMode() != DRA::Portrait ? 
		MAKEINTRESOURCE(IDD_WMLF_MAIN_WIDE) : 
		MAKEINTRESOURCE(IDD_WMLF_MAIN));
}
#endif

void FxMainWin::OnClose()
{
	if (m_BuddyOpt)
		delete m_BuddyOpt;
	m_BuddyOpt = NULL;

	CDialog::OnClose();
}

//::GetCaretPos(&point);
BOOL FxMainWin::PreTranslateMessage(MSG* pMsg)
{
	#if 1
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN: 
			if(pMsg->hwnd == view.m_hWnd)
			{
				//::AfxMessageBox(_T("_t"));
				showMsgDlg(view.GetSelectedItem());
			}
		case VK_ESCAPE: 
			return TRUE;
		default:
			break;

		}
	}
	#endif
	
#if DEBUG_GUI
#else
	if (pMsg->hwnd == this->m_hWnd)
	{
		if (handleFx_Sys_Event(pMsg->message, pMsg->wParam, pMsg->lParam))
			return TRUE;
	} else 
	if (pMsg->hwnd == view.m_hWnd)
	{
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			SHRGINFO shrg;
			shrg.cbSize = sizeof(shrg);
			shrg.hwndClient = pMsg->hwnd;
			shrg.ptDown.x = LOWORD(pMsg->lParam); 
			shrg.ptDown.y = HIWORD(pMsg->lParam); 
			shrg.dwFlags = SHRG_RETURNCMD; 
			CPoint point;
			point.x = shrg.ptDown.x;
			point.y = shrg.ptDown.y;
			if(::SHRecognizeGesture(&shrg) == GN_CONTEXTMENU)//长按键消息
			{ if (showBuddyMenu(point)) return TRUE; }
			else
			{	if (showMsgDlg(point)) return TRUE;  }
		}
	} 
#endif
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL FxMainWin::showBuddyMenu(CPoint point)
{
	UINT uFlags;
	HTREEITEM hItem = view.HitTest(point, &uFlags);

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
		return showBuddyMenu(hItem);
	return FALSE;
}

BOOL FxMainWin::showBuddyMenu(HTREEITEM hItem)
{
	if(hItem != view.GetSelectedItem())
		return FALSE;

	RECT r;
	CMenu menu;
	UINT nIDRes; 

	view.GetItemRect(hItem, &r, FALSE);

	CPoint point(r.left, r.top);

	if (view.GetParentItem(hItem))
		nIDRes = IDR_MENU_BUDDY;
	else
		return FALSE; // no impl the grup menu//nIDRes = IDR_MENU_GROUP;

	if (!menu.LoadMenu(nIDRes))
		return FALSE;

	CMenu *pPopupMenu = menu.GetSubMenu(0);
	ClientToScreen(&point);
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

	return TRUE;
}

BOOL FxMainWin::showMsgDlg(CPoint point)
{
	UINT uFlags;
	HTREEITEM hItem = view.HitTest(point, &uFlags);

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
		return showMsgDlg(hItem);
	return FALSE;
}

BOOL FxMainWin::showMsgDlg(HTREEITEM hItem)
{	
	if(hItem != view.GetSelectedItem())
		return FALSE;

	RECT r;
	view.GetItemRect(hItem, &r, FALSE);

	#if DEBUG_GUI
#else
	if (!view.GetParentItem(hItem))
		return FALSE;

	Account_Info *ac_info =(Account_Info*)view.GetItemData(hItem);
	if (!ac_info)
		return FALSE;

	POSITION pos = filker.Find(hItem);
	if (pos)
		filker.RemoveAt(pos);

	if (filker.GetCount() == 0)
			KillTimer(TIMER_NEWMSG);
#endif
	m_currentItem = hItem;
#if DEBUG_GUI
	m_currentMsgDlg = new FxMsgDlg(123456, this);
#else
	m_currentMsgDlg = new FxMsgDlg(ac_info->accountID, this);
#endif
	//this->ShowWindow(SW_HIDE);
	m_currentMsgDlg->m_isLoginOK = this->m_isLoginOK;
	m_currentMsgDlg->DoModal();
	
	//fix: this is a bad code, 
	//here will make sure that just have one msg dialog in system
	delete m_currentMsgDlg;
	//this->ShowWindow(SW_SHOW);
	m_BuddyOpt->setOnlineState(hItem);
	m_currentMsgDlg = NULL;
	m_currentItem = NULL;
	
	return TRUE;
}

bool FxMainWin::hand_SystemNetErr(int errcode)
{
	this->m_isLoginOK = FALSE;
	GetDlgItem(IDC_NET_STATE)->ShowWindow(SW_SHOW);
	if(this->m_currentMsgDlg)
	{
		this->m_currentMsgDlg->GetDlgItem(IDC_NET_STATE)->ShowWindow(SW_SHOW);
		//this->m_currentMsgDlg->GetDlgItem(IDC_SEND)->ShowWindow(SW_HIDE);
		this->m_currentMsgDlg->GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
		this->m_currentMsgDlg->GetDlgItem(IDC_SEND_MSG)->EnableWindow(FALSE);
	}
	relogin_fetion();
	this->UpdateWindow();
	return true;
}

void FxMainWin::relogin_ok()
{
	this->m_isLoginOK = TRUE;
	
	//set the fetion system msg call back function
	fx_set_system_msg_cb (Sys_EventListener, this);

	GetDlgItem(IDC_NET_STATE)->ShowWindow(SW_HIDE);
	if(this->m_currentMsgDlg)
	{
		this->m_currentMsgDlg->GetDlgItem(IDC_NET_STATE)->ShowWindow(SW_HIDE);
		//this->m_currentMsgDlg->GetDlgItem(IDC_SEND)->ShowWindow(SW_SHOW);
		this->m_currentMsgDlg->GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
		this->m_currentMsgDlg->GetDlgItem(IDC_SEND_MSG)->EnableWindow(TRUE);
	}
}

void FxMainWin::relogin_fetion()
{
	KillTimer(TIMER_RELOGIN);
	SetTimer(TIMER_RELOGIN, 1000*35, NULL);
	//fx_relogin(Relogin_EventListener, this);
	fx_relogin(Sys_EventListener, this);
}

void FxMainWin::update_account_info()
{
	Account_Info * ac_info = m_BuddyOpt->fetchNoUpdateAccount();
	if (ac_info)
	{
		fx_update_account_info_by_id(ac_info->accountID);
		m_BuddyOpt->setHaveUpdateAccount(ac_info);
	} else {
		KillTimer(TIMER_UPDATE_ACCOUNTINFO);
	}
}

void FxMainWin::OnTimer(UINT_PTR nIDEvent)
{
switch(nIDEvent)
	{
	case TIMER_NEWMSG:  //1/3秒刷新一次
		filker_newmsg();
		break;
	case TIMER_RELOGIN:
		relogin_fetion();
		break;
	case TIMER_UPDATE_ACCOUNTINFO:
		update_account_info();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


void FxMainWin::filker_newmsg()
{
	static bool state = false;
	int counts = filker.GetCount();
	for(int i = 0; i < counts; i++)
	{
		POSITION pos = filker.FindIndex(i);
		if (!pos)
			continue;
		HTREEITEM hItem = filker.GetAt(pos);
		if (state)
		{
			//fix: bad code 14 is empty icon. 13 is qun icon
			view.SetItemImage(hItem, 14, 14);
			view.SetItemImage(view.GetParentItem(hItem), 14, 14);
		} else {
			m_BuddyOpt->setOnlineState(hItem);
			view.SetItemImage(view.GetParentItem(hItem), 13, 13);
		}

	}
	state = !state;
}


#define MSG_OK       1
#define MSG_FAIL     2
#define MSG_TIMEOUT  3
#define MSG_FAIL_LIMIT  4


void FxMainWin::hand_MsgSend_Event(int message, int fx_msg, long who)
{
switch(message)
	{
		case FX_SMS_OK: 
		case FX_DIA_SEND_OK: 
		case FX_QUN_SEND_OK: 
		case FX_QUN_SMS_OK: 
			handle_sendmsg( MSG_OK, fx_msg, who);
			if(!fx_msg)
				return;
			fx_destroy_msg((Fetion_MSG *)fx_msg);
			break;
		case FX_SMS_FAIL: 
		case FX_DIA_SEND_FAIL: 
		case FX_QUN_SEND_FAIL: 
		case FX_QUN_SMS_FAIL: 
			handle_sendmsg( MSG_FAIL, fx_msg, who);
			if(!fx_msg)
				return;
			fx_destroy_msg((Fetion_MSG *)fx_msg);
			break;
		case FX_SMS_TIMEOUT: 
		case FX_DIA_SEND_TIMEOUT: 
		case FX_QUN_SEND_TIMEOUT: 
		case FX_QUN_SMS_TIMEOUT: 
			handle_sendmsg( MSG_TIMEOUT, fx_msg, who);
			//time out should not to destroy msg, beacuse the system will resend by itself..
			break;

		case FX_SMS_FAIL_LIMIT: 
		case FX_QUN_SMS_FAIL_LIMIT: 
			handle_sendmsg( MSG_FAIL_LIMIT , fx_msg, who);
			fx_destroy_msg((Fetion_MSG *)fx_msg);
			break;
	}

}

void FxMainWin::handle_sendmsg(int msgflag, int fx_msg, long account_id)
{
	if(!fx_msg)
		return;

	POSITION pos = NULL; 
	int i = 0;
	Fetion_MSG *fxMsg = (Fetion_MSG *) fx_msg;
	char *msg = fx_msg_no_format(fxMsg->message); 
	CString newmsg;
	
	switch(msgflag)
	{
		case MSG_OK:
			pos = timeOutMsgVector.Find(fx_msg);
			if (pos)
			{
				//newmsg = "<b style=\"color:rgb(170,0,255);\">" +tr("auto resend ok:") + "</b>" + newmsg.fromUtf8(msg);
				newmsg = CString(_T("自动重发OK:\r\n")) + ConvertUtf8ToUtf16(msg);
				addNewMessage(account_id, newmsg);
				timeOutMsgVector.RemoveAt(pos);
			}
			break;
		case MSG_FAIL:
			pos = timeOutMsgVector.Find(fx_msg);
			if (pos)
				timeOutMsgVector.RemoveAt(pos);
			//newmsg = "<b style=\"color:red;\">"+tr("send fail:") +"</b>"+ newmsg.fromUtf8(msg);
			newmsg = CString(_T("发送失败:\r\n")) + ConvertUtf8ToUtf16(msg);
			addNewMessage(account_id, newmsg);
			break;

		case MSG_FAIL_LIMIT:
			pos = timeOutMsgVector.Find(fx_msg);
			if (pos)
				timeOutMsgVector.RemoveAt(pos);
			//newmsg = "<b style=\"color:red;\">"+tr("send sms fail by limit:") +"</b>"+ newmsg.fromUtf8(msg);
			newmsg = CString(_T("发送数目限制:\r\n")) + ConvertUtf8ToUtf16(msg);
			addNewMessage(account_id, newmsg);
			break;
		case MSG_TIMEOUT:
			timeOutMsgVector.InsertAfter(timeOutMsgVector.GetTailPosition(), fx_msg);
			//newmsg = "<b style=\"color:rgb(170,0,255);\">" +tr("send timeout:") +"</b>" + newmsg.fromUtf8(msg)+"<br><b style=\"color:rgb(170,0,255);\">" +tr("will auto resend")+"</b>";
			newmsg = CString(_T("发送超时:\r\n")) + ConvertUtf8ToUtf16(msg);
			addNewMessage(account_id, newmsg);
			break;
	}

	if(msg)
		free(msg);
}

void FxMainWin::addNewMessage(long account_id, CString newmsg /* ="" */)
{
	TMPMSG_Info * msg_info = NULL;
	const Fetion_Account * account = fx_get_account_by_id (account_id);
	if (!account)
		return;

	HTREEITEM accountItem = m_BuddyOpt->findAccountItem(account);

	if (accountItem == m_currentItem && m_currentMsgDlg)
	{
		m_currentMsgDlg->addNewMsg(newmsg);
		return;
	}

	if (!newmsg.IsEmpty())
	{
		msg_info = new TMPMSG_Info;
		msg_info->accountID = account_id;
		msg_info->msg = newmsg;
		tmpMsg.InsertAfter(tmpMsg.GetTailPosition(), msg_info);
	}

	if (accountItem)
	{
		if (filker.GetCount() == 0)
			SetTimer(TIMER_NEWMSG, 300,NULL);
		filker.InsertAfter(filker.GetTailPosition(), accountItem);
	}
}