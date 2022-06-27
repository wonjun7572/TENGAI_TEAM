#include "pch.h"
#include "BossMonster.h"
#include "Bullet.h"


CBossMonster::CBossMonster()
	:iReverse(1), iReverse2(1), m_pBullet_Player(nullptr), m_pBullet_BossMonster(nullptr)
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo = { 125.f,125.f,50.f,50.f };
	m_fSpeed = 1.5f;
	m_tStat = { 50 };
	//iBoss_Hp = 50;

	m_dwTimer = GetTickCount();
}

int CBossMonster::Update(void)
{
	fCos = (fAngle * DGREE_TO_RADIAN);
	fSin = (fAngle * DGREE_TO_RADIAN);

	if (m_dead)
	{
		return OBJ_DEAD;
	}

	if (m_tStat.Hp <= 0)
	{
		m_dead = OBJ_DEAD;
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

void CBossMonster::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tRect.left - 20, m_tRect.top + 20, m_tRect.right + 20, m_tRect.bottom - 20);


}

void CBossMonster::Release(void)
{
}

void CBossMonster::Attack()
{
	if (m_dwTimer < GetTickCount())
	{
		// 앞으로 나가는 총알

		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER));

		// 

		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
		m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER));

		m_dwTimer = (GetTickCount() + 700);
	}



	//if (m_dwTimer < GetTickCount())
	//{
	//	// 밑으로 쏘는거
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX *20.f, m_tInfo.fY - 5.f, DIR_DOWN, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER));


	//	// 앞으로 쏘는거
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFT, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_UP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX *20.f, m_tInfo.fY - 5.f, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX - 20.f, m_tInfo.fY - 5.f, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER));
	//	m_pBullet_BossMonster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + 20.f, m_tInfo.fY - 5.f, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER));

	//	m_dwTimer = (GetTickCount() + 5000);
	//}

	if (m_dwTimer < GetTickCount())
	{
		// 왼쪽으로 나가는 총알
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER2));

		//// 오른쪽으로 나가는 총알
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER2));

		//// 위 쪽으로 나가는 총알
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER2));

		//// 밑 쪽으로 나가는 총알
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER2));
		//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER2));

		//m_dwTimer = (GetTickCount() + 500);
	}

	//if (m_dwTimer < GetTickCount())
	//{
	//	if (m_dwTimer < GetTickCount())
	//	{
	//		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX += fCos * m_fSpeed, m_tInfo.fY -= fSin * m_fSpeed, DIR_UP, OBJ_BULLET_BOSSMONSTER2));
	//		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER2));
	//		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER2));
	//		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX += fCos * m_fSpeed, m_tInfo.fY += fSin * m_fSpeed, DIR_DOWN, OBJ_BULLET_BOSSMONSTER2));

	//		/*m_dwTimer = (GetTickCount() + 750);*/
	//		fCos = -cos(fAngle * DGREE_TO_RADIAN);
	//}
}
