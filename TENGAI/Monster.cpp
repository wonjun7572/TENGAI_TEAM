#include "pch.h"
#include "Monster.h"

CMonster::CMonster()
	:iReverse(1)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo = { 700.f,500.f,75.f,75.f };
	m_fSpeed = 5.f;
}

int CMonster::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	m_tInfo.fY += 10 * iReverse;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate(void)
{
	if (m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
	{
		iReverse *= -1;
	}

	for (list<CObj*>::iterator iter = m_pBullet->begin();
		iter != m_pBullet->end();)
	{
		if (CollisionCheck(m_tRect, (*iter)->GetRect()))
		{
			m_dead = OBJ_DEAD;
			(*iter)->SetDead(OBJ_DEAD);
			break;
		}
		else
		{
			++iter;
		}
	}
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}