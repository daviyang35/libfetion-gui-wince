#include "StdAfx.h"
#include "Notify.h"

CNotify::CNotify(void)
{
}

CNotify::~CNotify(void)
{
}

// ����ָ������������
// ���strPath��Ϊ��, �򲥷�����
void CNotify::Nodify(CString strPath, int iPeriod, bool bVibe)
{
    StartViberate(bVibe);
    // TODO ��������ָ���ĳ���

    StopViberate(bVibe);
}

void CNotify::StartViberate(bool bVibe)
{
    if(!bVibe)
        return;
    // TODO ��ʼ��
}

void CNotify::StopViberate(bool bVibe)
{
    if(!bVibe)
        return;

    // TODO ֹͣ��
}