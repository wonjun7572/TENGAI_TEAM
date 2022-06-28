#include "pch.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()
	:m_pBullet_Player(nullptr), m_pBullet_Monster(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 400.f, 400.f, 30.f, 90.f };
	m_fSpeed = 10.f;
	m_dwTimer = GetTickCount();
	m_tStat.Hp = 10;
	m_tStat.UltimateCount = 1;
	m_tStat.BulletCount = 10;
}

int CPlayer::Update(void)
{
	if (m_tStat.Hp <= 0)
		m_dead = OBJ_DEAD;

	if (m_dead)
		return OBJ_DEAD;

	bShooting = false;
	Key_Input();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate(void)
{
	if (m_tInfo.fX < 50)
		m_tInfo.fX += m_fSpeed;

	if (m_tInfo.fX > WINCX - 50)
		m_tInfo.fX -= m_fSpeed;

	if (m_tInfo.fY < 50)
		m_tInfo.fY += m_fSpeed;

	if (m_tInfo.fY > WINCY - 50)
		m_tInfo.fY -= m_fSpeed;
}

void CPlayer::Render(HDC hDC)
{
	if (m_tStat.Hp <= 0)
		m_dead = OBJ_DEAD;

	if (bShooting == false)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom - 60.f);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);

		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 15.f, nullptr);
		LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 15.f);
		LineTo(hDC, m_tInfo.fX - 15.f, m_tInfo.fY + 30.f);

		// ¿À¸¥ÂÊ ´Ù¸®
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 15.f, nullptr);
		LineTo(hDC, m_tInfo.fX + 15.f, m_tInfo.fY + 30.f);

		// ¿ÞÂÊ ÆÈ
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 5.f, nullptr);
		LineTo(hDC, m_tInfo.fX - 17.f, m_tInfo.fY - 2.f);

		//¿À¸¥ÂÊ ÆÈ
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 5.f, nullptr);
		LineTo(hDC, m_tInfo.fX + 17.f, m_tInfo.fY - 2.f);
	}
	else if (bShooting == true)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom - 60.f);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);


		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 15.f, nullptr);
		LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 15.f);
		LineTo(hDC, m_tInfo.fX - 15.f, m_tInfo.fY + 30.f);

		// ¿À¸¥ÂÊ ´Ù¸®
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 15.f, nullptr);
		LineTo(hDC, m_tInfo.fX + 15.f, m_tInfo.fY + 15.f);
		LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 30.f);

		// ¿ÞÂÊ ÆÈ
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 5.f, nullptr);
		LineTo(hDC, m_tInfo.fX + 5.f, m_tInfo.fY - 10.f);
		LineTo(hDC, m_tInfo.fX + 17.f, m_tInfo.fY - 10.f);

		////¿À¸¥ÂÊ ÆÈ
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 5.f, nullptr);
		LineTo(hDC, m_tInfo.fX + 17.f, m_tInfo.fY - 2.f);
	}

	for (int i = 0; i < m_tStat.Hp; i++)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0xff, 0x00, 0x00));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Rectangle(hDC, (10 + (i * 50)), 10, (50 + (i * 50)), 50);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);


		WCHAR szBuff[32] = L"HP";
		TextOut(hDC, (10 + (i * 50)), 10, szBuff, lstrlen(szBuff));
	}

	for (int i = 0; i < m_tStat.UltimateCount; i++)
	{
		m_tStat.hNewBrush = CreateSolidBrush(RGB(0x00, 0x00, 0xff));
		m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
		Rectangle(hDC, (10 + (i * 50)), 60, (50 + (i * 50)), 100);
		SelectObject(hDC, m_tStat.hOldBrush);
		DeleteObject(m_tStat.hNewBrush);

		WCHAR szBuff[32] = L"Ultimate";
		TextOut(hDC, (10 + (i * 50)), 60, szBuff, lstrlen(szBuff));
	}
}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP)) // ¿À¸¥ÂÊ À­´ë°¢¼± 
		{
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) // ¿À¸¥ÂÊ ¾Æ·§ ´ë°¢¼±
		{
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else // ±×³É ¿À¸¥ÂÊ¸¸ ´­·¶À»‹š 
		{
			m_tInfo.fX += m_fSpeed;
		}

	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP)) // ¿ÞÂÊ À­´ë°¢¼± 
		{
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) // ¿ÞÂÊ ¾Æ·§ ´ë°¢¼±
		{
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else // ±×³É ¿À¸¥ÂÊ¸¸ ´­·¶À»‹š 
		{
			m_tInfo.fX -= m_fSpeed;
		}

	}
	else if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		bShooting = true;
		if (m_dwTimer < GetTickCount())
		{
			for (int i = 1; i < m_tStat.BulletCount + 1; i++)
			{
				m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY - (10.f *i), DIR_RIGHT, OBJ_BULLET_PLAYER));
			}
			m_dwTimer = GetTickCount() + 200;
		}
	}

	if (GetAsyncKeyState(VK_CONTROL))
	{
		if (m_tStat.UltimateCount != 0)
		{
			if (m_dwTimer < GetTickCount())
			{
				for (int i = 0; i < 10; ++i)
				{
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_PLAYER));
					m_pBullet_Player->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_PLAYER));
					m_dwTimer = GetTickCount() + (50 * i);
				}
				m_tStat.UltimateCount--;
			}
		}
	}
}

