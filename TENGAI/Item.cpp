#include "pch.h"
#include "Item.h"




CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	m_tInfo = { 700.f,500.f,45.f,45.f };
	m_fSpeed = 5.f;
}

int CItem::Update(void)
{
	if (m_dead == true)
		return OBJ_DEAD;

	//m_tInfo.fY += 10 * iReverse;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate(void)
{
}

void CItem::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CItem::Release(void)
{
}