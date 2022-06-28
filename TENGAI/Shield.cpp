#include "pch.h"
#include "Shield.h"



CShield::CShield()
	:m_fAngle(0), m_fDiagonal(100)
{
}


CShield::~CShield()
{
}


void CShield::Initialize(void)
{
	m_tInfo = { 400.f, 400.f, 15.f, 15.f };
	//m_fSpeed = 10.f;
	//m_dwTimer = GetTickCount();
	m_tStat.Hp = 3;
	m_tStat.UltimateCount = 0;
	m_tStat.BulletCount = 0;
}

int CShield::Update(void)
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

	m_fAngle += 10.f;

	m_tInfo.fX = m_pPlayer->GetInfo().fX + m_fDiagonal*cosf(m_fAngle *(PI / 180));
	m_tInfo.fY = m_pPlayer->GetInfo().fY - m_fDiagonal*sinf(m_fAngle *(PI / 180));


	Update_Rect();

	return OBJ_NOEVENT;

}

void CShield::LateUpdate(void)
{

}

void CShield::Render(HDC hDC)
{
	if (m_bEffect)
	{
		m_fExplosion += 0.5;
		Ellipse(hDC, m_tRect.left - m_fExplosion, m_tRect.top - m_fExplosion, m_tRect.right + m_fExplosion, m_tRect.bottom + m_fExplosion);
	}
	else
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CShield::Release(void)
{
}
