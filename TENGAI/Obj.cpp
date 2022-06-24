#include "pch.h"
#include "Obj.h"


CObj::CObj() : m_eDir(DIR_END), m_dead(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tStat, sizeof(m_tStat));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

// �� �� ���ϰ� ����ϱ� ���� bool check�� ��������ϴ�.
bool CObj::CollisionCheck(RECT rc1, RECT rc2)
{
	if (IntersectRect(&RECT(), &rc1, &rc2))
	{
		return true;
	}

	return false;
}
