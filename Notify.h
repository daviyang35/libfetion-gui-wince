#pragma once

class CNotify
{
public:
    CNotify(void);
    ~CNotify(void);
    // ����ָ��������
    static void Nodify(CString strPath, int iPeriod, bool bVibe);
private:
    static void StartViberate(bool bVibe);
    static void StopViberate(bool bVibe);
};
