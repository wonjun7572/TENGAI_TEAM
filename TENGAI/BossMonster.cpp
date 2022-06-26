#include "pch.h"
#include "BossMonster.h"
#include "Bullet.h"


CBossMonster::CBossMonster()
	:iReverse(1), iReverse2(1), m_pBullet_Player(nullptr), m_pBullet_BossMonster(nullptr),
	bPattern_A(false), bPattern_B(false), bPattern_C(false), iBoss_Hp(0)
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f,50.f,50.f };
	m_fSpeed = 1.5f;
	iBoss_Hp = 50;

	m_dwTimer = GetTickCount();
}

int CBossMonster::Update(void)
{
	fCos = (fAngle * DEGREE_TO_RADIAN);
	fSin = (fAngle * DEGREE_TO_RADIAN);


	if (m_dead)
	{
		return OBJ_DEAD;
	}

	/*m_tInfo.fX += m_fSpeed * iReverse;
	m_tInfo.fY += m_fSpeed * iReverse;*/
	m_tInfo.fX += fCos * m_fSpeed * iReverse;
	m_tInfo.fY += fSin * m_fSpeed * iReverse2;

	fAngle += 1;
	if (fAngle >= 360)
		fAngle = 0;




	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::LateUpdate(void)
{
	if (30 <= iBoss_Hp)
	{
		if (m_tInfo.fY < 0)
		{
			iReverse2 *= -1;
		}

		else if (m_tInfo.fY < -1 || m_tInfo.fX <1)
		{
			iReverse2 *= -1;
			iReverse *= -1;
		}

		if (m_tInfo.fX > WINCX)
		{
			iReverse *= -1;
		}
		if (m_tInfo.fX <0)
		{
			iReverse2 *= -1;
		}
		if (m_tInfo.fY > WINCY)
		{
			iReverse2 *= -1;
		}
	}

}

void CBossMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


}

void CBossMonster::Release(void)
{
}

void CBossMonster::Attack()
{
	// 랜덤으로 패턴 출력을 위해 0~99까지 값이 매번 랜덤하게 나오도록 함
	srand((unsigned int)time(nullptr) + GetTickCount());
	int iRandomPattern = rand() % 99;

	// 몬스터 기준으로 3방향 총알 쏘는 패턴
	if (m_dwTimer < GetTickCount() && (0 == (iRandomPattern % 3)) && (bPattern_A == false))
	{
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN));
		m_dwTimer = (GetTickCount() + 1000);

		// 해당 bool변수가 true이면 다음 회전시 해당 패턴이 발생하지 않음
		bPattern_A = true;
		bPattern_B = false;
		bPattern_C = false;
	}

	//	보스 기준, 맵 좌표 기준으로 나감
	// 패턴 A
	// m_dwTimer < GetTickCount() && (0 == (iRandomPattern % 3)) && (bPattern_A == false)
	// m_dwTimer = (GetTickCount() + 1000);
	bPattern_A = true;
	if (GetAsyncKeyState('w'))
	{
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(600, 100, DIR_LEFT));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(620, 200, DIR_LEFT));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(640, 300, DIR_LEFT));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(660, 400, DIR_LEFT));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(680, 500, DIR_LEFT));

		bPattern_A = true;
		bPattern_B = false;
		bPattern_C = false;
	}

	// 패턴 B
	/*if (m_dwTimer < GetTickCount() && (1 == (iRandomPattern % 3)) && (bPattern_B == false))
	{
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(680, 100, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(660, 200, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(640, 300, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(620, 400, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(600, 500, DIR_LEFT));
	m_dwTimer = (GetTickCount() + 1000);

	bPattern_A = false;
	bPattern_B = true;
	bPattern_C = false;
	}*/

	// 패턴 C
	/*if (m_dwTimer < GetTickCount() && (2 == (iRandomPattern % 3)) && (bPattern_C == false))
	{
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(600, 100, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(570, 150, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(550, 200, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(540, 250, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(530, 300, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(540, 350, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(550, 400, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(570, 450, DIR_LEFT));
	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(600, 500, DIR_LEFT));
	m_dwTimer = (GetTickCount() + 1000);

	bPattern_A = false;
	bPattern_B = false;
	bPattern_C = true;
	}*/
	/*m_dwTimer < GetTickCount()
	m_dwTimer = GetTickCount() + 1000;*/
	// 평타
	if (10 >= iBoss_Hp)
	{
		if (m_dwTimer < GetTickCount())
		{
			// 밑으로 쏘는거
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFT));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHT));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX *20.f, m_tInfo.fY - 5.f, DIR_DOWN));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFTDOWN));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHTDOWN));


			// 앞으로 쏘는거
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFT));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_UP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX *20.f, m_tInfo.fY - 5.f, DIR_RIGHTUP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFTUP));
			m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHTUP));

			m_dwTimer = GetTickCount() + 1000;
		}



		bPattern_A = false;
		bPattern_B = false;
		bPattern_C = false;
	}
}
