#include "pch.h"
#include "Monster_Level_04.h"
#include "Item.h"
#include "Player.h"
#include "AddHpItem.h"
#include "Bullet.h"
#include "CollisionMgr.h"


CMonster_Level_04::CMonster_Level_04()
{
}


CMonster_Level_04::~CMonster_Level_04()
{
}

void CMonster_Level_04::Initialize(void)
{
	m_tInfo = { 700.f,500.f,70.f,50.f };
	m_fSpeed = 10.f;
	m_dwTimer = GetTickCount();
	m_tStat = { 10 };
}

int CMonster_Level_04::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	if (m_tStat.Hp <= 0)
	{
		m_dead = OBJ_DEAD;
	}

	// 실패의 흔적 -> atan은 -90 ~ 90 각도밖에 계산할 수 없다!
	// 탄젠트 그래프를 보면 그 이유를 알 수 있다!
	//float X = fabs((m_pPlayer->front()->GetInfo().fX) - m_tInfo.fX);
	//float Y = fabs((m_pPlayer->front()->GetInfo().fY) - m_tInfo.fY);
	//float tan = atanf(Y / X);
	//fCos = cos(tan);
	//fSin = sin(tan);

	if (m_dwTimer + 5000 >= GetTickCount())
	{
		float X = (m_pPlayer->front()->GetInfo().fX) - m_tInfo.fX;
		float Y = (m_pPlayer->front()->GetInfo().fY) - m_tInfo.fY;
		m_fAtan = atan2f(Y, X);
		m_fCos = cos(m_fAtan);
		m_fSin = sin(m_fAtan);
		m_tInfo.fX -= 0.5f;
	}

	if (m_dwTimer + 5000 < GetTickCount())
	{
		Attack();
	}
	//m_tInfo.fX += (m_fSpeed * iReverse * fCos);
	//m_tInfo.fY += (m_fSpeed * iReverse * fSin);

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster_Level_04::LateUpdate(void)
{
	/*
	if (m_tInfo.fX < 0 || m_tInfo.fX > WINCY)
	{
	iReverse *= -1;
	}*/
	//if (m_tRect.left <= g_WindowRect.left
	//	|| m_tRect.right >= g_WindowRect.right
	//	|| m_tRect.top <= g_WindowRect.top
	//	|| m_tRect.bottom >= g_WindowRect.bottom)
	//{
	//iReverse *= -1;
	//	m_dead = true;
	//}
	//if(CCollisionMgr::CollisionWall(m_tRect))
	if (m_dead)
	{
		CreateItem();
	}
}

void CMonster_Level_04::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// 아크탄젠트 : 높이 / 밑변 입력시 높이의 대각 출력
	// 180도밖에 안되는 이유? -> 아크탄젠트2, atan2(높이, 밑면)
	// 아크탄젠트는 두 점 사이의 상대적인 거리를 측정하는 방식으로
	// 마이너스 좌표계로 이동해도 연산이 가능하다!!
	// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=h2ohyukhyuk&logNo=140181926921
	//m_tStat.hNewBrush = CreateSolidBrush(RGB(0x00, 0xff, 0xff));
	//m_tStat.hOldBrush = (HBRUSH)SelectObject(hDC, m_tStat.hNewBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//SelectObject(hDC, m_tStat.hOldBrush);
	//DeleteObject(m_tStat.hNewBrush);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX + (100 * m_fCos), m_tInfo.fY + (100 * m_fSin));
}

void CMonster_Level_04::Release(void)
{
}



void CMonster_Level_04::Attack()
{
	m_tInfo.fX += (m_fSpeed * iReverse * m_fCos);
	m_tInfo.fY += (m_fSpeed * iReverse * m_fSin);
}
