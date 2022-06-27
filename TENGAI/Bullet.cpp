#include "pch.h"
#include "Bullet.h"

CBullet::CBullet()
	:m_pMonster(nullptr)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 5.f;
	m_tStat = { 1 };
	m_dwTimer = GetTickCount();
}

int CBullet::Update(void)
{
	if (m_tStat.Hp <= 0)
	{
		SetEffect();
		if (10.f <= m_fExplosion)
			m_dead = OBJ_DEAD;
	}

	if (m_dead)
	{
		return OBJ_DEAD;
	}

	switch (m_eDir)
	{
	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case DIR_LEFTUP:
		m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		break;
	case DIR_LEFTDOWN:
		m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		break;
	case DIR_RIGHTUP:
		m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		break;
	case DIR_RIGHTDOWN:
		m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		break;
	case DIR_CHASE:
		m_tInfo.fX += (m_fSpeed * m_fCos) / sqrtf(2.f);
		m_tInfo.fY += (m_fSpeed * m_fSin) / sqrtf(2.f);
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate(void)
{
	if (m_eObjID == OBJ_BULLET_PLAYER)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0x00, 0x00, 0xff));
	}
	else if (m_eObjID == OBJ_BULLET_PET)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0x00, 0xff, 0x00));
	}
	else if (m_eObjID == OBJ_BULLET_MONSTER)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0xff, 0x00));
	}
	else if (m_eObjID == OBJ_BULLET_BOSSMONSTER)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
	}
}

void CBullet::Render(HDC hDC)
{
	if (m_bEffect)
	{
		m_fExplosion += 0.5;
		//m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x77, 0x00));
		//m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left - m_fExplosion, m_tRect.top - m_fExplosion, m_tRect.right + m_fExplosion, m_tRect.bottom + m_fExplosion);
		//SelectObject(hDC, m_tStat.hOldBrush);
		//DeleteObject(m_tStat.hNewBrush);

	}
	else
	{
		//m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		//SelectObject(hDC, m_tStat.hOldBrush);
		//DeleteObject(m_tStat.hNewBrush);

	}
}

void CBullet::Release(void)
{
}
