/***************************************************************************
 *   Copyright (C) 2008 by DDD                                          *
 *   dedodong@163.com                                                     *
 ***************************************************************************/
#ifndef FXBUDDY_H
#define FXBUDDY_H

#define I_OFFLINE 0
#define I_BLACK 1
#define I_MOBILE 2
#define I_WAITING_AUTH 3
#define I_REFUSE 4
#define I_DINNER 5
#define I_AWAY 6
#define I_ONLINE 7
#define I_PHONE 8
#define I_BUSY 9
#define I_MEETING 10
#define I_EXAWAY 11
#define I_NUM_PRIMITIVES 12
#define I_QUN 13
#define I_FLICK 14
#define I_END 15

class BuddyOpt
{
	public:
		BuddyOpt(CTreeCtrl * Widget);
		~BuddyOpt();

		int  markedCount;
		BOOL isQunItem(HTREEITEM); 
		
		void freeAllGroupdata();    
		void freeAllAccountdata(HTREEITEM);    
		void freeAllQundata(HTREEITEM);    
		void addGroupToTree();    
		void addAccountToTree();  
		void addQunToTree();

		void delAccount_direct(long uid);  
		void delAccount(long uid);  
		void delAccount(HTREEITEM accountItem); 

		void delGroup(long id);  
		void addGroup(const char* groupname, long id);  

		void addAccountToGroup(const Fetion_Account *account); 
		void addAccountToGroup(const Fetion_Account *account, CString & name, int online_state, int group ); 

		void updateAccountInfo(long account_id);
		CString createAccountTipsInfo(const Fetion_Account *account);
		void setTipsOfAccount(HTREEITEM  accountItem, const Fetion_Account *account);

		HTREEITEM findAccountItem(const Fetion_Account *account);
		HTREEITEM findAccountItemFromGroup(HTREEITEM  groupItem, const Fetion_Account *account);
		HTREEITEM findGroupItemByID(int group_id);

		Account_Info *fetchNoUpdateAccount();
		void setHaveUpdateAccount(Account_Info *);

		void setOnlineState(HTREEITEM hItem);
		int getOnlineIcon(int flag);

		void expandTree();
		void m_itemChanged();
		void updateStyles(HTREEITEM  *item, int column);
  
private:
		BOOL isOnlineStateChanged(int old_state, int new_state, int* state);
		int init_icon(void);
		void setOnlineState(HTREEITEM hItem, int flag);

private:
		CTreeCtrl *treeWidget;
		HTREEITEM QunItem;
		BOOL have_zero_group; 
		CBitmap pBitmap[I_END]; 
		CImageList m_imagelist;
};


#endif