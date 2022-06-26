#include "pch.h"
#include "AddUltimateItem.h"
#include "Player.h"

CAddUltimateItem::CAddUltimateItem()
{
}


CAddUltimateItem::~CAddUltimateItem()
{
}

void CAddUltimateItem::Initialize(void)
{
	m_tInfo = { 700.f,500.f,45.f,45.f };
	m_fSpeed = 3.f;
}

int CAddUltimateItem::Update(void)
{
	if (m_dead == true)
	{
		dynamic_cast<CPlayer*>(GetPlayer())->UltimateCountUp();
		return OBJ_DEAD;
	}

	m_tInfo.fX -= m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CAddUltimateItem::LateUpdate(void)
{
	if (CollisionCheck(GetPlayer()->GetRect(), m_tRect))
	{
		m_dead = OBJ_DEAD;
	}
}

void CAddUltimateItem::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	WCHAR szBuff[32] = L"ULTIMATE";
	TextOut(hDC, m_tRect.left + 6.f, m_tRect.top + 10.f, szBuff, lstrlen(szBuff));
}

void CAddUltimateItem::Release(void)
{
}

bool CAddUltimateItem::CollisionCheck(RECT r1, RECT r2)
{
	RECT rc = {};

	if (IntersectRect(&rc, &r1, &r2))
	{
		return true;
	}

	return false;
}
