#include "pch.h"
#include "AddShieldItem.h"
#include "Player.h"
#include "Shield.h"
#include "AbstractFactory.h"


CAddShieldItem::CAddShieldItem()
	:m_fDiagonal(0), m_fAngle(0), m_Arrive(false)
{

}


CAddShieldItem::~CAddShieldItem()
{
}

void CAddShieldItem::Initialize(void)
{
	m_tStat.Hp = 1;
	m_tInfo = { 700.f,500.f,45.f,45.f };
	m_fSpeed = 3.f;
	m_fDiagonal = 100;
}

int CAddShieldItem::Update(void)
{

	if (m_dead == true)
	{
		dynamic_cast<CPlayer*>(GetPlayer())->Set_ShieldCheck(true);

		return OBJ_DEAD;
	}



	m_tInfo.fX -= m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}



void CAddShieldItem::LateUpdate(void)
{
	if (CollisionCheck(GetPlayer()->GetRect(), m_tRect))
		m_dead = OBJ_DEAD;
}

void CAddShieldItem::Render(HDC hDC)
{
	m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0xff));
	m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, m_tStat.hOldBrush);
	DeleteObject(m_tStat.hNewBrush);


	WCHAR szBuff[32] = L"Shield";
	TextOut(hDC, m_tRect.left + 6.f, m_tRect.top + 10.f, szBuff, lstrlen(szBuff));
}

void CAddShieldItem::Release(void)
{
}

bool CAddShieldItem::CollisionCheck(RECT r1, RECT r2)
{
	RECT rc = {};

	if (IntersectRect(&rc, &r1, &r2))
		return true;

	return false;
}