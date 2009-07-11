// FindBuddyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WMLF.h"
#include "FindBuddyDlg.h"

// CFindBuddyDlg �Ի���

IMPLEMENT_DYNAMIC(CFindBuddyDlg, CDialog)

CFindBuddyDlg::CFindBuddyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindBuddyDlg::IDD, pParent)
{

}

CFindBuddyDlg::~CFindBuddyDlg()
{
}

void CFindBuddyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFindBuddyDlg, CDialog)
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CFindBuddyDlg ��Ϣ�������

void CFindBuddyDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    int iMargin = DRA::SCALEX(5);
    int iX, iY, iW, iH;
    int iInfoX, iInfoY, iInfoW, iInfoH; //��ʾ�û���Ϣ�����LIST��ΪҪ���Գ���,���Ե����ñ�������,�������

    HWND hwndDlg = this->m_hWnd;
    RECT rcDlg;
    ::GetClientRect(hwndDlg, &rcDlg);

	HWND hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_RD_MOBILE);
	ASSERT(hwndCtl != NULL);
	RECT rcCtl;
	::GetWindowRect(hwndCtl, &rcCtl);
    iX = rcDlg.left + iMargin;
    iY = rcDlg.top + iMargin;
    iW = rcCtl.right - rcCtl.left;
    iH = rcCtl.bottom - rcCtl.top;
    ::MoveWindow(hwndCtl, iX, iY, iW, iH, false);
    
    iInfoX = iX;
    iInfoW = rcDlg.right - rcDlg.left - 2 * iMargin;

    hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_RD_FXNO);
    ::MoveWindow(hwndCtl, iX + iW + iMargin, iY, iW, iH, false);

    hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_EDIT_NO);
	::GetWindowRect(hwndCtl, &rcCtl);
    iY = iY + iH + iMargin;
    iW = rcDlg.right - rcDlg.left - 20 - iMargin * 2;
    iH = rcCtl.bottom - rcCtl.top;
    ::MoveWindow(hwndCtl, iX, iY, iW, iH, false);

    iInfoY = iY + iH + iMargin; //�����Info��Y����,��ΪiH���,������ǰ�ȼӺ÷���

    hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_BTN_FIND);
    iX = rcDlg.left + iW + iMargin;
    iW = 20;
    iH = 20;
    ::MoveWindow(hwndCtl, iX, iY, iW, iH, false);

    hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_EDIT_NAME);
    ::GetWindowRect(hwndCtl, &rcCtl);
    iX = rcDlg.left + iMargin;
    iY = rcDlg.bottom - (rcCtl.bottom - rcCtl.top) - iMargin;
    iH = rcCtl.bottom - rcCtl.top;
    iW = rcDlg.right - rcDlg.left - 2 * iMargin;
    ::MoveWindow(hwndCtl, iX, iY, iW, iH , false);

    hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_STATIC_NAME);
    ::GetWindowRect(hwndCtl, &rcCtl);
    iW = rcCtl.right - rcCtl.left;
    iH = rcCtl.bottom - rcCtl.top;
    iY = iY - iMargin - iH;
    ::MoveWindow(hwndCtl, iX, iY, iW, iH, false);

    iInfoH = iY - iMargin - iInfoY;

    hwndCtl = ::GetDlgItem(hwndDlg, IDC_FB_LIST_INFO);
    ::MoveWindow(hwndCtl, iInfoX, iInfoY, iInfoW, iInfoH, true);
}

BOOL CFindBuddyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	if (!m_dlgCommandBar.Create(this) ||
		!m_dlgCommandBar.InsertMenuBar(IDR_MENU_FINDBUDDY))
	{
		TRACE0("δ�ܴ��� CommandBar\n");
		return FALSE;      // δ�ܴ���
	}
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
