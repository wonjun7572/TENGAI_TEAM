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
	m_tInfo = { 400.f, 300.f, 50.f, 50.f };
	m_fSpeed = 10.f;
	dwTimer = GetTickCount() + 200;
	m_tStat = { 3 };
}

int CPlayer::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	Key_Input();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate(void)
{
	// 범위 밖으로 못벗아나게 해주는 함수
	if(m_tInfo.fX < 50)
		m_tInfo.fX += m_fSpeed;
	
	if (m_tInfo.fX > WINCX - 50)
		m_tInfo.fX -= m_fSpeed;

	if (m_tInfo.fY < 50)
		m_tInfo.fY += m_fSpeed;

	if (m_tInfo.fY > WINCY - 50)
		m_tInfo.fY -= m_fSpeed;




	/*for (auto &iter : *m_pMonster)
	{
		if (CollisionCheck(m_tRect,iter->GetRect()))
		{
			if (dwTimer + 700 < GetTickCount())
			{
				m_tStat.Hp -= 1;
				dwTimer = GetTickCount();
			}
		}
	}*/
	// 에러 부분
	
}

void CPlayer::Render(HDC hDC)
{
		
	if (m_tStat.Hp <= 0)
	{
		m_dead = OBJ_DEAD;
	}

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	for (int i = 0; i < m_tStat.Hp; i++)
	{
		Rectangle(hDC, (10+(i*50)), 10, (50 + (i * 50)), 50);
	}
}

void CPlayer::Release(void)
{

}



void CPlayer::Key_Input(void)
{
	// 대각선 구하는 공식 1:루트2 : 10: x => 10*루트 2 = x 그래서 스피드는 스피드/루트 2
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP)) // 오른쪽 윗대각선 
		{
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) // 오른쪽 아랫 대각선
		{
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		}
		else // 그냥 오른쪽만 눌렀을떄 
		{
			m_tInfo.fX += m_fSpeed;
		}

	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP)) // 왼쪽 윗대각선 
		{
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN)) // 왼쪽 아랫 대각선
		{
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
			m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		}
		else // 그냥 오른쪽만 눌렀을떄 
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









	/*if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;*/

	// GetKeyState로 활성화 할수 있고 비활성화 할 수 있는 것도 아이디어 추가하면 좋을듯.

	if (GetAsyncKeyState(VK_SPACE))
	{

		if (dwTimer + 200 < GetTickCount())
		{
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
			dwTimer = GetTickCount();
		}
	}
}

