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
	/*
	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;
	m_fDiagonal = 20.f;

	m_bStart = true;*/

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

	if (m_eObjID == OBJ_BULLET_PET)
	{
		if (m_pMonster->empty() &&  m_pBossMonster->empty())
		{
			
		}
		else if (m_pMonster->empty())
		{
			m_fAtan = atan2f(m_pBossMonster->front()->GetInfo().fY - m_tInfo.fY, m_pBossMonster->front()->GetInfo().fX - m_tInfo.fX);
			m_fCos = cos(m_fAtan);
			m_fSin = sin(m_fAtan);
		}
		else
		{
			m_fAtan = atan2f(m_pMonster->front()->GetInfo().fY - m_tInfo.fY, m_pMonster->front()->GetInfo().fX - m_tInfo.fX);
			m_fCos = cos(m_fAtan);
			m_fSin = sin(m_fAtan);
		}
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
		/*
	case DIR_SCREW:
		if (m_bStart)
		{
			m_tCenter.x = long(m_tInfo.fX);
			m_tCenter.y = long(m_tInfo.fY);

			m_bStart = false;
		}

		m_tCenter.x -= long(m_fSpeed * cosf(m_fAngle * (PI / 180.f)));
		m_tCenter.y -= long(m_fSpeed * sinf(m_fAngle * (PI / 180.f)));

		m_fRotAngle += m_fRotSpeed;

		m_tInfo.fX = m_tCenter.x + m_fDiagonal * cosf(m_fRotAngle * (PI / 180.f));
		m_tInfo.fY = m_tCenter.y - m_fDiagonal * sinf(m_fRotAngle * (PI / 180.f));

		break;*/

		}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate(void)
{
	//if (m_eObjID == OBJ_BOSSMONSTER)
	//{
	//	m_tPosin.x = LONG(m_tInfo.fX + cosf(m_fAngle * (PI / 180.f)) * m_fDiagonal);
	//	m_tPosin.y = LONG(m_tInfo.fY - sinf(m_fAngle * (PI / 180.f)) * m_fDiagonal);
	//}
}

void CBullet::Render(HDC hDC)
{
	if (m_bEffect)
	{
		DeleteObject(m_tStat.hNewBrush);
		m_fExplosion += 0.5;
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x77, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left - m_fExplosion, m_tRect.top - m_fExplosion, m_tRect.right + m_fExplosion, m_tRect.bottom + m_fExplosion);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);
	}
	else
	{
		
 		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, m_tStat.hOldBrush);
	}
}

void CBullet::Release(void)
{
	DeleteObject(m_tStat.hNewBrush);
}
