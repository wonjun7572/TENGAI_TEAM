#include "pch.h"
#include "Monster_Level_02.h"
#include "Item.h"
#include "AddHpItem.h"
#include "Bullet.h"

CMonster_Level_02::CMonster_Level_02()
{
}


CMonster_Level_02::~CMonster_Level_02()
{
}

void CMonster_Level_02::Initialize(void)
{
	m_tInfo = { 700.f,500.f,50.f,30.f };
	m_fSpeed = 2.f;
	m_dwTimer2 = GetTickCount();
	m_tStat = { 3 };
}

int CMonster_Level_02::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	if (m_tStat.Hp <= 0)
	{
		m_dead = OBJ_DEAD;
	}

	m_tInfo.fX -= m_fSpeed;

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Level_02::LateUpdate(void)
{
	if (m_dead)
		CreateItem();
}

void CMonster_Level_02::Render(HDC hDC)
{
	m_tStat.hNewBrush = CreateSolidBrush(RGB(0xf0, 0x64, 0x64));
	m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, m_tStat.hOldBrush);
	DeleteObject(m_tStat.hNewBrush);
}

void CMonster_Level_02::Release(void)
{
}

void CMonster_Level_02::Attack()
{
	if (m_dwTimer2 < GetTickCount())
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_MONSTER));
		m_dwTimer2 = (GetTickCount() + 1000);
	}
}
