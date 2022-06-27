#include "pch.h"
#include "Pet.h"
#include "Bullet.h"
#include "AbstractFactory.h"

CPet::CPet()
	:m_pPlayer(nullptr), m_pBullet_Pet(nullptr)
{
}

CPet::~CPet()
{
}

void CPet::Initialize(void)
{
	m_tInfo = { 400.f, 400.f, 15.f, 15.f };
	m_fSpeed = 10.f;
	m_dwTimer = GetTickCount();
	m_tStat.Hp = 3;
	m_tStat.UltimateCount = 1;
	m_tStat.BulletCount = 1;
	
}

int CPet::Update(void)
{
	X = (m_pPlayer->front()->GetInfo().fX - 15.f) - m_tInfo.fX;
	Y = (m_pPlayer->front()->GetInfo().fY - 60.f) - m_tInfo.fY;
	fAtan = atan2f(Y, X);
	fCos = cos(fAtan);
	fSin = sin(fAtan);

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPet::LateUpdate(void)
{
	
	if (m_dwTimer < GetTickCount())
	{
		if (fabs(fOldTimeX - m_tInfo.fX) >= 5.f || fabs(fOldTimeY - m_tInfo.fY) >= 5.f)
			fStop = 1.f;
		else
			fStop = 0.f;

		m_tInfo.fX += (m_fSpeed * fCos) * fStop;
		m_tInfo.fY += (m_fSpeed * fSin) * fStop;
		num++;

		if (num % 25 == 0)
		{
			for (int i = 1; i < m_tStat.BulletCount + 1; i++)
			{
				m_pBullet_Pet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY - (10.f *i), DIR_RIGHT, OBJ_PET));
			}
		}

		m_dwTimer = GetTickCount() + 30;
	}
	fOldTimeX = m_pPlayer->front()->GetInfo().fX - 15.f;
	fOldTimeY = m_pPlayer->front()->GetInfo().fY - 60.f;


	
}

void CPet::Render(HDC hDC)
{
	//m_tStat.hNewBrush = CreateSolidBrush(RGB(0x00, 0xff, 0xff));
	//m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//SelectObject(hDC, m_tStat.hOldBrush);
	//DeleteObject(m_tStat.hNewBrush);
}

void CPet::Release(void)
{
}
