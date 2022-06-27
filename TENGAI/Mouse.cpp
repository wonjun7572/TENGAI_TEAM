#include "pch.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMouse::Update(void)
{
	POINT	pt{};

	// ��ũ�� ��ǥ ������ ���콺 ���� ����
	GetCursorPos(&pt);

	// �츮�� ������ ������ â �������� ���콺 ��ǥ�� ����
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	Update_Rect();

	ShowCursor(false);

	return OBJ_NOEVENT;
}

void CMouse::LateUpdate(void)
{

}

void CMouse::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release(void)
{

}
