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
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 5.f;
}

int CBullet::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

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
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR_RIGHTUP:
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
		break;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate(void)
{
	// 원래부터 충돌되고 있으니 충돌이 되지 않을 때 죽음으로 처리
	if (!CollisionCheck(m_tRect,g_WindowRect))
	{
		m_dead = OBJ_DEAD;
	}

	for (auto &iter : *m_pMonster)
	{
		if (IntersectRect(&RECT(), &m_tRect, &iter->GetRect()) && m_pMonster!=nullptr)
		{
			iter->SetDead(true);
		}

	}
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}
