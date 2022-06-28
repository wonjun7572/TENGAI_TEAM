#include "pch.h"
#include "BossMonster.h"
#include "Bullet.h"


CBossMonster::CBossMonster()
	:iReverse(1), iReverse2(1), m_pBullet_Player(nullptr), m_pBullet_BossMonster(nullptr)
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f,50.f,50.f };
	m_fSpeed = 1.5f;
	m_tStat.Hp = 50;

	m_dwTimer = GetTickCount();
}

int CBossMonster::Update(void)
{
	fCos = (fAngle * DEGREE_TO_RADIAN);
	fSin = (fAngle * DEGREE_TO_RADIAN);

	if (m_dead)
		return OBJ_DEAD;

	if (m_tStat.Hp <= 0)
	{
		SetEffect();
		if (50.f <= m_fExplosion)
			m_dead = OBJ_DEAD;
	}
	
	m_tInfo.fX += fCos * m_fSpeed * iReverse;
	m_tInfo.fY += fSin * m_fSpeed * iReverse2;

	fAngle += 1;
	
	if (fAngle >= 360)
		fAngle = 0;

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::LateUpdate(void)
{
	if (m_tInfo.fY < 0)
	{
		iReverse2 *= -1;
	}

	else if (m_tInfo.fY < -1 || m_tInfo.fX <1)
	{
		iReverse2 *= -1;
		iReverse *= -1;
	}

	if (m_tInfo.fX > WINCX + 100)
	{
		iReverse *= -1;
	}
	if (m_tInfo.fX <0)
	{
		iReverse2 *= -1;
	}
	if (m_tInfo.fY > WINCY)
	{
		iReverse2 *= -1;
	}
}

void CBossMonster::Render(HDC hDC)
{
	if (m_bEffect)
	{
		DeleteObject(m_tStat.hNewBrush);
		m_fExplosion += 5.f;
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0xff, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left - m_fExplosion, m_tRect.top - m_fExplosion, m_tRect.right + m_fExplosion, m_tRect.bottom + m_fExplosion);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);
	}
	else
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);

		m_tStat.hNewBrush = CreateSolidBrush(RGB(0x00, 0xff, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left - 20, m_tRect.top + 20, m_tRect.right + 20, m_tRect.bottom - 20);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);
	}

	TCHAR		szBuff[32] = L"";
	RECT	rc{ 300, 200, 500, 300 };
	swprintf_s(szBuff, L"BOSS HP :  %d", m_tStat.Hp);
	DrawText(hDC, szBuff, lstrlen(szBuff), &rc, DT_CENTER);
}

void CBossMonster::Release(void)
{
}

void CBossMonster::Attack()
{
	// 처음 몬스터가 풀피일떄 사용하는 공격 패턴
	if (m_tStat.Hp >= 25)
	{
		if (m_dwTimer < GetTickCount())
		{
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER));

			m_dwTimer = (GetTickCount() + 700);
		}
	}
	else
	{
		if (m_dwTimer < GetTickCount())
		{
			// 밑으로 쏘는거
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX *20.f, m_tInfo.fY - 5.f, DIR_DOWN, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER));

			// 앞으로 쏘는거
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_UP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX *20.f, m_tInfo.fY - 5.f, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));

			m_dwTimer = (GetTickCount() + 700);
		}
	}
}