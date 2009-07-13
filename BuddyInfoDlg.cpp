// BuddyInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WMLF.h"
#include "BuddyInfoDlg.h"


#ifdef M8
#include "M8Misc.h"
#endif

#ifdef WIN32_PLATFORM_WFSP
#include <tpcshell.h>
#endif
// CBuddyInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CBuddyInfoDlg, CDialog)

CBuddyInfoDlg::CBuddyInfoDlg(long lAccountID, CWnd* pParent /*=NULL*/)
	: CDialog(CBuddyInfoDlg::IDD, pParent)
    , m_strShowName(_T(""))
    , m_iGroupID(0)
    , m_lAccountID(lAccountID)
    , m_strNickName(_T(""))
    , m_strName(_T(""))
    , m_strSex(_T(""))
    , m_strProv(_T(""))
    , m_strCity(_T(""))
    , m_strSign(_T(""))
{
}

CBuddyInfoDlg::~CBuddyInfoDlg()
{
}

void CBuddyInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_BI_EDT_SHOWNAME, m_strShowName);
    DDX_Text(pDX, IDC_BI_FETIONNO, m_lAccountID);
    DDX_Text(pDX, IDC_BI_NICKNAME, m_strNickName);
    DDX_Text(pDX, IDC_BI_NAME, m_strName);
    DDX_Text(pDX, IDC_BI_SEX, m_strSex);
    DDX_Text(pDX, IDC_BI_PROV, m_strProv);
    DDX_Text(pDX, IDC_BI_CITY, m_strCity);
    DDX_Text(pDX, IDC_BI_SIGN, m_strSign);
    DDX_Control(pDX, IDC_BI_CBO_GROUP, m_cboGroup);
}


BEGIN_MESSAGE_MAP(CBuddyInfoDlg, CDialog)
    ON_WM_SIZE()
    ON_WM_VSCROLL()
    ON_COMMAND(IDOK, &CBuddyInfoDlg::OnOk)
END_MESSAGE_MAP()


// CBuddyInfoDlg ��Ϣ�������

BOOL CBuddyInfoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
#ifdef M8
    AddMenuBarForM8(this->GetSafeHwnd(), IDR_MENU_BUDDYINFO);
    FullScreen(this->GetSafeHwnd());
#else
	if (!m_dlgCommandBar.Create(this) ||
		!m_dlgCommandBar.InsertMenuBar(IDR_MENU_BUDDYINFO))
	{
		TRACE0("δ�ܴ��� CommandBar\n");
		return FALSE;      // δ�ܴ���
	}
#endif

    InitGroupItem();
    fx_update_account_info_by_id (m_lAccountID);
	m_account = fx_get_account_by_id(m_lAccountID);
    if(NULL == m_account)
        return FALSE;

    m_strShowName =  ConvertUtf8ToUtf16(m_account->local_name);
    m_iGroupID = fx_get_account_group_id(m_account);
    m_strNickName = ConvertUtf8ToUtf16(m_account->personal->nickname);
    m_strSex = m_account->personal->gender == 1? _T("˧��") : _T("��Ů");
    m_strProv = ConvertUtf8ToUtf16(m_account->personal->province);
    m_strCity = _T("");//ConvertUtf8ToUtf16(m_account->personal->city);
    m_strSign = ConvertUtf8ToUtf16(m_account->personal->impresa);

    for(int i = 0; i < m_cboGroup.GetCount() && i < 25; i++)
    {
        if(m_iGroupID == m_iGroupIDs[i])
        {
            m_cboGroup.SetCurSel(i);
            break;
        }
    }

    UpdateData(FALSE);
    InitScrollInfo();
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CBuddyInfoDlg::InitScrollInfo()   
{   
    RECT rect;
    this->GetWindowRect(&rect);   
    SCROLLINFO si;   
    si.cbSize = sizeof(SCROLLINFO);   
    si.fMask = SIF_ALL; // SIF_ALL = SIF_PAGE | SIF_RANGE | SIF_POS;   
    si.nMin = 0;   
    RECT minutesRect;   
    GetDlgItem(IDC_BI_GRP_INFO)->GetWindowRect(&minutesRect);   
    si.nMax = minutesRect.bottom;   
    si.nPage =  rect.bottom - rect.top;
    if(si.nMax <= rect.bottom)   
    {   
        si.nMax = 0;   
    } 
  
    si.nPos = 0;   
    SetScrollInfo(SB_VERT, &si, TRUE);   
}

void CBuddyInfoDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
 
    int iHeight, iWidth;
    int iMargin = DRA::SCALEY(5);

    RECT rcCtl;
    ::GetClientRect(this->m_hWnd, &rcCtl);
#ifdef M8
    rcCtl.top += 40;
#endif

    iHeight = rcCtl.bottom - rcCtl.top; //����߶�
    iWidth = rcCtl.right - rcCtl.left;  //������

    int iX, iY, iW, iH;
    int iWLabel, iHLabel;
    int iXValue, iWValue, iHValue;
    
    int iXGroup2, iYGroup2, iWGroup2, iHGroup2; //�ڶ���GROUPBOX�������ݵ�����С,�����������

    iWLabel = DRA::SCALEX(70);
    iHLabel = DRA::SCALEX(18);

    
    iWValue = iWidth - 5 * iMargin - iWLabel;
    iHValue = DRA::SCALEX(20);

    iX = rcCtl.left + iMargin;
    iY = rcCtl.top + iMargin;
    iW = iWidth - 2*iMargin;
    iH = 2 * DRA::SCALEY(20) + 3 * iMargin + DRA::SCALEY(14);

    //��������GROUP

    HWND hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_GRP_SET);
    ::MoveWindow(hwndctl,  iX, iY, iW, iH, SWP_NOZORDER | SWP_NOREDRAW);
    iXGroup2 = iX;
    iYGroup2 = iY + iMargin + iH;
    iWGroup2 = iW;


    //���������е��ڲ��ؼ�
    iX += iMargin;
    iXValue = iX + iMargin + iWLabel;
    iY = rcCtl.top + iMargin + iHValue;
    
    //��ʼһ��
    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_SHOWNAME);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_EDT_SHOWNAME);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);

    iY = iY + iHValue + iMargin ;
    //��������һ��
    //��һ��,����
    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_GROUP);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_CBO_GROUP);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    //��һ��

    iY = iY + iHValue + 2 * iMargin + iHValue; //�������Group����,���һ��iMargin

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_FETIONNO);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_FETIONNO);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    
    iY = iY + iHValue + iMargin ;
    //

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_NICKNAME);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_NICKNAME);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    
    iY = iY + iHValue + iMargin ;
    //

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_NAME);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_NAME);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    
    iY = iY + iHValue + iMargin ;
    //

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_SEX);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_SEX);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    
    iY = iY + iHValue + iMargin ;
    //

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_PROV);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_PROV);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    
    iY = iY + iHValue + iMargin ;
    //
    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_CITY);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_CITY);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, iHValue, FALSE);
    
    iY = iY + iHValue + iMargin ;
    //
    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_LB_SIGN);
    ::MoveWindow(hwndctl,  iX, iY, iWLabel, iHLabel, FALSE);

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_SIGN);
    ::MoveWindow(hwndctl,  iXValue, iY, iWValue, DRA::SCALEY(20) * 2, FALSE);
    
    iHGroup2 = iY + DRA::SCALEY(20) * 2 + iMargin - iYGroup2;

    hwndctl = ::GetDlgItem(this->m_hWnd, IDC_BI_GRP_INFO);
    ::MoveWindow(hwndctl, iXGroup2, iYGroup2, iWGroup2, iHGroup2, TRUE);

    InitScrollInfo();
}


void CBuddyInfoDlg::InitGroupItem(void)
{	
    Fetion_Group *group = NULL;

	DList *tmp_group = (DList *)fx_get_group();
    int i = 0;
	while(tmp_group)
	{
		group = (Fetion_Group *) tmp_group->data;
		if(group) {
			m_cboGroup.AddString(ConvertUtf8ToUtf16(group->name));
            if(i<25)
                m_iGroupIDs[i] = group->id;
            i++;
		}
		tmp_group = d_list_next(tmp_group);
	}  
}

void CBuddyInfoDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    SCROLLINFO si = {   sizeof(SCROLLINFO),    
        SIF_PAGE|SIF_POS|SIF_RANGE|SIF_TRACKPOS,    
        0, 0, 0, 0,    
        0   
    };   
    int imi = si.nPos;   
    GetScrollInfo(SB_VERT, &si);   
    switch (nSBCode)   
    {           
    case SB_TOP:   
        si.nPos = si.nMin;   
        break;   
    case SB_BOTTOM:   
        si.nPos = si.nMax - si.nPage;   
        break;   
    case SB_LINEDOWN:   
        if(si.nPos + si.nPage < si.nMax)   
        {   
            SetScrollPos(SB_VERT, GetScrollPos(SB_VERT)+5);   
            ::ScrollWindowEx(m_hWnd,0,-5,NULL, NULL,NULL, NULL,SW_ERASE|SW_SCROLLCHILDREN);       
        }   
        break;           
    case SB_LINEUP:    
        if(si.nPos > si.nMin)   
        {   
            SetScrollPos(SB_VERT, GetScrollPos(SB_VERT)-5);   
            ::ScrollWindowEx(m_hWnd,0,5,NULL, NULL,NULL, NULL,SW_ERASE|SW_SCROLLCHILDREN);       
        }   
        if(si.nPos < si.nMin)   
            si.nPos = si.nMin;         
        break;        
    case SB_THUMBPOSITION:   
        SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) + nPos - si.nPos);   
        ::ScrollWindowEx(m_hWnd,0,si.nPos - nPos,NULL, NULL,NULL, NULL,SW_ERASE|SW_SCROLLCHILDREN);       
        break;   
    case SB_PAGEUP:   
        if(si.nPos > si.nMin)   
        {   
            SetScrollPos(SB_VERT, GetScrollPos(SB_VERT)-5);   
            ::ScrollWindowEx(m_hWnd,0,5,NULL, NULL,NULL, NULL,SW_ERASE|SW_SCROLLCHILDREN);       
        }   
        if(si.nPos < si.nMin)   
            si.nPos = si.nMin;         
        break;        
  
    case SB_PAGEDOWN:   
        if(si.nPos + si.nPage < si.nMax)   
        {   
            SetScrollPos(SB_VERT, GetScrollPos(SB_VERT)+5);   
            ::ScrollWindowEx(m_hWnd,0,-5,NULL, NULL,NULL, NULL,SW_ERASE|SW_SCROLLCHILDREN);       
        }   
        break;     
    }

    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CBuddyInfoDlg::OnOk()
{
    UpdateData();
    int iNewGroupID = m_iGroupIDs[m_cboGroup.GetCurSel()];
    if(m_iGroupID != iNewGroupID)
    {
        fx_move_group_buddy_by_id(m_lAccountID, iNewGroupID, NULL, NULL);
    }
    if(m_strShowName != ConvertUtf8ToUtf16(m_account->local_name))
    {
        fx_set_buddyinfo(m_lAccountID, ConvertUtf16ToUtf8(m_strShowName), NULL, NULL); 
    }
    CDialog::OnOK();
}

void CBuddyInfoDlg::OnCancel()
{
#ifdef WIN32_PLATFORM_WFSP
	// �������޸ĺ��˼�����ΪΪɾ��EditBox�е����ݣ��������˳�ģ̬�Ի���
	SHSendBackToFocusWindow(WM_HOTKEY, 2, MAKELPARAM(MOD_KEYUP, VK_TBACK));
#else
	CDialog::OnCancel();
#endif // WIN32_PLATFORM_W
}
