#include "pch.h"
#include "Monster.h"
#include "Item.h"

CMonster::CMonster()
	:iReverse(1) , m_pBullet(nullptr),m_pItem(nullptr)
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
	if (m_dead == true)
		return OBJ_DEAD;

	m_tInfo.fX += 10 * iReverse;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate(void)
{
	if (m_tInfo.fX < 0 || m_tInfo.fX > WINCY)
	{
		iReverse *= -1;
	}

	for (list<CObj*>::iterator iter = m_pBullet->begin();
		iter != m_pBullet->end();)
	{
		if (CollisionCheck(m_tRect, (*iter)->GetRect()))
		{
			m_dead = true;
			(*iter)->SetDead(OBJ_DEAD);
       		CreateItem();
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

void CMonster::CreateItem()
{
	// 아이템 생성
	m_pItem->push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY,DIR_END));
}


