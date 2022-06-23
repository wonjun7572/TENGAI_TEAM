#include "pch.h"
#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 5.f;
}

int CBullet::Update(void)
{
	if (m_dead == true)
		return OBJ_DEAD;

	switch (m_eDir)
	{
	case DIR_UP:
		m_tInfo.fY -= 10;
		break;
	case DIR_DOWN:
		m_tInfo.fY += 10;
		break;
	case DIR_LEFT:
		m_tInfo.fX -= 10;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += 10;
		break;
	case DIR_LEFTUP:
		m_tInfo.fX -= 10;
		m_tInfo.fY -= 10;
		break;
	case DIR_RIGHTUP:
		m_tInfo.fX += 10;
		m_tInfo.fY -= 10;
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate(void)
{
	if (m_tInfo.fX < 70 || m_tInfo.fX > WINCX - 70
		|| m_tInfo.fY < 70 || m_tInfo.fY > WINCY - 70)
	{
		m_dead = true;
	}
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}
