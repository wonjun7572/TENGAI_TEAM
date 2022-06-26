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
}

int CBullet::Update(void)
{
	if (m_tStat.Hp <= 0)
	{
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

}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}
