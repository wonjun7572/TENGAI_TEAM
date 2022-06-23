#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()
	:m_pBullet(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}


void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 300.f, 100.f, 100.f };
	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	Key_Input();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input(void)
{
	//GetKeyState()

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState(W))
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP));

	if (GetAsyncKeyState(A))
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));

	if (GetAsyncKeyState(S))
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));

	if (GetAsyncKeyState(D))
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP));
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP));
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP));
	}
}

