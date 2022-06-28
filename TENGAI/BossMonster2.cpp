#include "pch.h"
#include "BossMonster2.h"
#include "Bullet.h"

CBossMonster2::CBossMonster2()
	:iReverse(1), iReverse2(1), m_pBullet_Player(nullptr), m_pBullet_BossMonster2(nullptr),
	bAngle(false)
{
}


CBossMonster2::~CBossMonster2()
{
}

void CBossMonster2::Initialize(void)
{
	m_tInfo = { 150.f,150.f,200.f,200.f };	
	m_fSpeed = 3.f;
	m_tStat = { 50 };

	m_dwTimer = GetTickCount();
	m_dwTimer2 = GetTickCount();

	fAngle = 1.f;
}

int CBossMonster2::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	if (m_tStat.Hp <= 0)
		m_dead = OBJ_DEAD;

	if (m_dwTimer + 5000 >= GetTickCount())
		m_tInfo.fX -= 0.5f;

	else if (m_dwTimer < GetTickCount())
		Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster2::LateUpdate(void)
{
}

void CBossMonster2::Render(HDC hDC)
{
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 80);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 100);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 130);
	LineTo(hDC, m_tInfo.fX - 25, m_tInfo.fY + 230);
	LineTo(hDC, m_tInfo.fX + 30, m_tInfo.fY + 230);
	LineTo(hDC, m_tInfo.fX + 30, m_tInfo.fY + 130);
	MoveToEx(hDC, m_tInfo.fX + 30, m_tInfo.fY + 230, nullptr); //130
	LineTo(hDC, m_tInfo.fX + 130, m_tInfo.fY + 230);
	LineTo(hDC, m_tInfo.fX + 130, m_tInfo.fY + 130);
	LineTo(hDC, m_tInfo.fX + 110, m_tInfo.fY - 20);
	MoveToEx(hDC, m_tInfo.fX + 130, m_tInfo.fY + 130, nullptr);
	LineTo(hDC, m_tInfo.fX + 230, m_tInfo.fY + 130);
	LineTo(hDC, m_tInfo.fX + 230, m_tInfo.fY + 30);
	LineTo(hDC, m_tInfo.fX + 210, m_tInfo.fY + 10);
	LineTo(hDC, m_tInfo.fX + 115, m_tInfo.fY + 10);
	
	m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
	m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
	Ellipse(hDC, m_tInfo.fX - 20, m_tInfo.fY - 120, m_tInfo.fX + 130, m_tInfo.fY + 30);
	SelectObject(hDC, m_tStat.hOldBrush);
	DeleteObject(m_tStat.hNewBrush);
	
	m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
	m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
	Ellipse(hDC, m_tInfo.fX - 20, m_tInfo.fY - 110, m_tInfo.fX + 90, m_tInfo.fY - 20);
	SelectObject(hDC, m_tStat.hOldBrush);
	DeleteObject(m_tStat.hNewBrush);
}

void CBossMonster2::Release(void)
{
}

void CBossMonster2::Attack()
{
	if (fAngle < 180)
	{
		iReverse = +1;
		bAngle = true;
		fAngle2 = fAngle;
	}
	else if (fAngle2 == 0)
	{
		bAngle = true;
		fAngle = fAngle2;
		iReverse = +1;
	}

	else if (360 > fAngle && fAngle >= 180)
	{
		bAngle = false;
		iReverse2 = -1;
	}


	if (bAngle)
	{
		fAngle += 1.f * iReverse;
		fCos = cos(fAngle * DEGREE_TO_RADIAN);
		fSin = sin(fAngle * DEGREE_TO_RADIAN);
	}
	else if (!bAngle)
	{
		fAngle2 += 1.f * iReverse2;
		fCos = cos(fAngle2 * DEGREE_TO_RADIAN);
		fSin = sin(fAngle2 * DEGREE_TO_RADIAN);
	}


	m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create_ChaseBullet(m_tInfo.fX, m_tInfo.fY, -fCos, fSin, DIR_CHASE, OBJ_BULLET_BOSSMONSTER2));
	m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create_ChaseBullet(m_tInfo.fX, m_tInfo.fY, fCos, -fSin, DIR_CHASE, OBJ_BULLET_BOSSMONSTER2));
}