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

	// ������ ���� -> atan�� -90 ~ 90 �����ۿ� ����� �� ����!
	// ź��Ʈ �׷����� ���� �� ������ �� �� �ִ�!
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

	// ��ũź��Ʈ : ���� / �غ� �Է½� ������ �밢 ���
	// 180���ۿ� �ȵǴ� ����? -> ��ũź��Ʈ2, atan2(����, �ظ�)
	// ��ũź��Ʈ�� �� �� ������ ������� �Ÿ��� �����ϴ� �������
	// ���̳ʽ� ��ǥ��� �̵��ص� ������ �����ϴ�!!
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
