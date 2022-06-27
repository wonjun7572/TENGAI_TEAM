#include "pch.h"
#include "BossMonster2.h"
#include "Bullet.h"


CBossMonster2::CBossMonster2()
	:iReverse(1), iReverse2(1), m_pBullet_Player(nullptr), m_pBullet_BossMonster2(nullptr)
{
}


CBossMonster2::~CBossMonster2()
{
}

void CBossMonster2::Initialize(void)
{
	//m_tInfo = { 125.f,125.f,50.f,50.f };	// 테스트 용도
	 m_tInfo = { 150.f,150.f,200.f,200.f };	// 이게 실전 사용 하는 보스 좌표
	m_fSpeed = 3.f;
	m_tStat = { 50 };

	m_dwTimer = GetTickCount();
}

int CBossMonster2::Update(void)
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

	/*m_tInfo.fX += fCos * m_fSpeed * iReverse;
	m_tInfo.fY += fSin * m_fSpeed * iReverse2;*/


	fAngle += 1.f;
	if (fAngle >= 360)
		fAngle = 0;

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster2::LateUpdate(void)
{
	/*if (m_tInfo.fX > WINCX +200 || m_tInfo.fX < 0)
	{
	iReverse *= -1;
	}

	if (m_tInfo.fY > WINCY +200 || m_tInfo.fY < 0)
	{
	iReverse *= 1;
	iReverse2 *= -1;
	}
	*/
	/*if (m_tInfo.fX < -200)
	{
	iReverse *= -1;
	}
	else if (m_tInfo.fX > +200)
	{
	iReverse2 *= -1;
	}

	if (m_tInfo.fY <-200)
	{
	iReverse2 *= -1;
	iReverse *= -1;
	}

	else if (m_tInfo.fY > +200)
	{
	iReverse *= -1;
	}*/
}

void CBossMonster2::Render(HDC hDC)
{

	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//Ellipse(hDC, m_tRect.left - 20, m_tRect.top + 20, m_tRect.right + 20, m_tRect.bottom - 20);


	MoveToEx(hDC,m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 80);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 100);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 130);
	LineTo(hDC, m_tInfo.fX - 25, m_tInfo.fY + 230);
	LineTo(hDC, m_tInfo.fX + 30, m_tInfo.fY + 230);
	LineTo(hDC, m_tInfo.fX + 30, m_tInfo.fY + 130);
	MoveToEx(hDC, m_tInfo.fX + 30, m_tInfo.fY + 230, nullptr); //130
	LineTo(hDC, m_tInfo.fX + 130, m_tInfo.fY + 230);
	LineTo(hDC, m_tInfo.fX + 130, m_tInfo.fY + 130);
	LineTo(hDC, m_tInfo.fX + 110, m_tInfo.fY - 20);
	MoveToEx(hDC, m_tInfo.fX + 130, m_tInfo.fY + 130, nullptr);
	LineTo(hDC, m_tInfo.fX + 230, m_tInfo.fY + 130);
	LineTo(hDC, m_tInfo.fX + 230, m_tInfo.fY + 30);
	LineTo(hDC, m_tInfo.fX + 210, m_tInfo.fY + 10);
	LineTo(hDC, m_tInfo.fX + 115, m_tInfo.fY + 10);
	Ellipse(hDC, m_tInfo.fX - 20, m_tInfo.fY - 120, m_tInfo.fX + 130, m_tInfo.fY + 30);
	Ellipse(hDC, m_tInfo.fX - 20, m_tInfo.fY - 110, m_tInfo.fX + 90, m_tInfo.fY - 20);

}

void CBossMonster2::Release(void)
{
}

void CBossMonster2::Attack()
{
	/*if (m_tInfo.fX > WINCX + 200 || m_tInfo.fX < 0)
	{
	iReverse *= -1;
	}

	if (m_tInfo.fY > WINCY + 200 || m_tInfo.fY < 0)
	{
	iReverse *= 1;
	iReverse2 *= -1;
	}*/

	//if (m_dwTimer < GetTickCount())
	//{
	//	// 왼쪽으로 나가는 총알
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER2));

	//	//// 오른쪽으로 나가는 총알
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER2));

	//	//// 위 쪽으로 나가는 총알
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTUP, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP, OBJ_BULLET_BOSSMONSTER2));

	//	//// 밑 쪽으로 나가는 총알
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHTDOWN, OBJ_BULLET_BOSSMONSTER2));
	//	//m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN, OBJ_BULLET_BOSSMONSTER2));

	//	//m_dwTimer = (GetTickCount() + 300000);
	//}

	if (m_dwTimer < GetTickCount())
	{
		fCos = cos(fAngle * DGREE_TO_RADIAN);

		fSin = sin(fAngle * DGREE_TO_RADIAN);

	//	/*case DIR_CHASE:
	//	m_tInfo.fX += (m_fSpeed * m_fCos) / sqrtf(2.f);
	//	m_tInfo.fY += (m_fSpeed * m_fSin) / sqrtf(2.f);*/


		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_CHASE, OBJ_BULLET_BOSSMONSTER2));
		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_CHASE, OBJ_BULLET_BOSSMONSTER2));
		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_CHASE, OBJ_BULLET_BOSSMONSTER2));
		m_pBullet_BossMonster2->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_CHASE, OBJ_BULLET_BOSSMONSTER2));

		m_tInfo.fX += fCos * fAngle;
		m_tInfo.fY += fSin * fAngle;


		/*m_dwTimer = (GetTickCount() + 750);*/
		fCos = -cos(fAngle * DGREE_TO_RADIAN);

	} 
}