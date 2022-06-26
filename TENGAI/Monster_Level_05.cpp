#include "pch.h"
#include "Monster_Level_05.h"
#include "Item.h"
#include "AddHpItem.h"
#include "Bullet.h"

CMonster_Level_05::CMonster_Level_05()
{
}


CMonster_Level_05::~CMonster_Level_05()
{
}

void CMonster_Level_05::Initialize(void)
{
	m_tInfo = { 700.f,500.f,70.f,70.f };
	m_fSpeed = 0.5f;
	m_dwTimer = GetTickCount();
	m_dwTimer2 = GetTickCount();
	m_tStat = { 20 };
}

int CMonster_Level_05::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	if (m_tStat.Hp <= 0)
	{
		m_dead = OBJ_DEAD;
	}

	if (m_dwTimer2 + 5000 >= GetTickCount())
	{
		float X = (m_pPlayer->front()->GetInfo().fX) - m_tInfo.fX;
		float Y = (m_pPlayer->front()->GetInfo().fY) - m_tInfo.fY;
		m_fAtan = atan2f(Y, X);
		m_fCos = cos(m_fAtan);
		m_fSin = sin(m_fAtan);
		m_tInfo.fX -= m_fSpeed;
	}

	if (m_dwTimer2 + 5000 < GetTickCount())
	{
		m_fSpeed = 0;
	}

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Level_05::LateUpdate(void)
{
	//if (m_tInfo.fX < 0 || m_tInfo.fX > WINCY)
	//{
	//	iReverse *= -1;
	//}
	if (m_dead)
	{
		CreateItem();
	}
}

void CMonster_Level_05::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX + (100 * m_fCos), m_tInfo.fY + (100 * m_fSin));
}

void CMonster_Level_05::Release(void)
{
}



void CMonster_Level_05::Attack()
{
	float X = (m_pPlayer->front()->GetInfo().fX) - m_tInfo.fX;
	float Y = (m_pPlayer->front()->GetInfo().fY) - m_tInfo.fY;
	m_fAtan = atan2f(Y, X);
	m_fCos = cos(m_fAtan);
	m_fSin = sin(m_fAtan);

	if (m_dwTimer < GetTickCount())
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create_ChaseBullet(m_tInfo.fX, m_tInfo.fY, m_fCos, m_fSin, DIR_CHASE, OBJ_BULLET_MONSTER));
		m_dwTimer = GetTickCount() + 500;
	}
}
