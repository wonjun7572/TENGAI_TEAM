#include "pch.h"
#include "Monster_Level_03.h"
#include "Item.h"
#include "AddHpItem.h"
#include "Bullet.h"


CMonster_Level_03::CMonster_Level_03()
{
}


CMonster_Level_03::~CMonster_Level_03()
{
}

void CMonster_Level_03::Initialize(void)
{
	m_tInfo = { 700.f,500.f,70.f,50.f };
	m_fSpeed = 0.f;
	m_dwTimer = GetTickCount();
}

int CMonster_Level_03::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	//if (m_dwTimer + 5000 < GetTickCount())
	//{
	//	m_tInfo.fX += m_fSpeed * iReverse;
	//	Attack();
	//}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Level_03::LateUpdate(void)
{
	if (m_tInfo.fX < 0 || m_tInfo.fX > WINCY)
	{
		iReverse *= -1;
	}
	if (m_dead)
	{
		CreateItem();
	}
}

void CMonster_Level_03::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster_Level_03::Release(void)
{
}

void CMonster_Level_03::CreateItem()
{
	m_pItem->push_back(CAbstractFactory<CAddHpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	for (auto& iter = m_pItem->begin(); iter != m_pItem->end(); ++iter)
	{
		dynamic_cast<CItem*>(*iter)->SetPlayer(m_pPlayer->front());
	}
}

void CMonster_Level_03::Attack()
{
	if (m_dwTimer < GetTickCount())
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_dwTimer = GetTickCount() + 1000;
	}
}
