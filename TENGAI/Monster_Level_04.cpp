#include "pch.h"
#include "Monster_Level_04.h"
#include "Item.h"
#include "AddHpItem.h"
#include "Bullet.h"

CMonster_Level_04::CMonster_Level_04()
{
}


CMonster_Level_04::~CMonster_Level_04()
{
}

void CMonster_Level_04::Initialize(void)
{
	m_tInfo = { 700.f,500.f,100.f,70.f };
	m_fSpeed = 3.f;
	m_dwTimer = GetTickCount();
}

int CMonster_Level_04::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Level_04::LateUpdate(void)
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

void CMonster_Level_04::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX + (100 * fCos), m_tInfo.fY + (100 * fSin));
}

void CMonster_Level_04::Release(void)
{
}

void CMonster_Level_04::CreateItem()
{
	m_pItem->push_back(CAbstractFactory<CAddHpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	for (auto& iter = m_pItem->begin(); iter != m_pItem->end(); ++iter)
	{
		dynamic_cast<CItem*>(*iter)->SetPlayer(m_pPlayer->front());
	}
}

void CMonster_Level_04::Attack()
{
	float X = (m_pPlayer->front()->GetInfo().fX) - m_tInfo.fX;
	float Y = (m_pPlayer->front()->GetInfo().fY) - m_tInfo.fY;
	fAtan = atan2f(Y, X);
	fCos = cos(fAtan);
	fSin = sin(fAtan);
}
