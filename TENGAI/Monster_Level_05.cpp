#include "pch.h"
#include "Monster_Level_05.h"
#include "Item.h"
#include "AddHpItem.h"

CMonster_Level_05::CMonster_Level_05()
{
}


CMonster_Level_05::~CMonster_Level_05()
{
}

void CMonster_Level_05::Initialize(void)
{
	m_tInfo = { 700.f,500.f,120.f,90.f };
	m_fSpeed = 3.f;
	m_dwTimer = GetTickCount();
}

int CMonster_Level_05::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed * iReverse;

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Level_05::LateUpdate(void)
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

void CMonster_Level_05::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster_Level_05::Release(void)
{
}

void CMonster_Level_05::CreateItem()
{
	m_pItem->push_back(CAbstractFactory<CAddHpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	for (auto& iter = m_pItem->begin(); iter != m_pItem->end(); ++iter)
	{
		dynamic_cast<CItem*>(*iter)->SetPlayer(m_pPlayer->front());
	}
}

void CMonster_Level_05::Attack()
{
}
