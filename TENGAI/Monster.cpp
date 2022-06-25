#include "pch.h"
#include "Monster.h"
#include "Item.h"
#include "Bullet.h"
#include "AddHpItem.h"

CMonster::CMonster()
	:iReverse(1), m_pBullet_Player(nullptr), m_pBullet_Monster(nullptr), m_pItem(nullptr),
	bPattern_A(false), bPattern_B(false), bPattern_C(false)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo = { 700.f,500.f,30.f,20.f };
	m_fSpeed = 3.f;
	m_dwTimer = GetTickCount();
}

int CMonster::Update(void)
{
	if (m_dead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed * iReverse;

	Attack();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::LateUpdate(void)
{
	if (m_tInfo.fX < 0 || m_tInfo.fX > WINCY)
	{
		iReverse *= -1;
	}
	if (m_dead)
	{
		CreateItem();
	}
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::CreateItem()
{
	// 아이템 생성
	// 무조건 아이템 생성은 아니고 랜덤으로 설정
	m_pItem->push_back(CAbstractFactory<CAddHpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	for (auto& iter = m_pItem->begin(); iter != m_pItem->end(); ++iter)
	{
		dynamic_cast<CAddHpItem*>(*iter)->SetPlayer(m_pPlayer->front());
	}
}

void CMonster::Attack()		// 몬스터 미사일 발사 코드, GetTickCount() + 원하는 시간값 입력
{
	// 랜덤으로 패턴 출력을 위해 0~99까지 값이 매번 랜덤하게 나오도록 함
	srand((unsigned int)time(nullptr) + GetTickCount());
	int iRandomPattern = rand() % 99;

	// 몬스터 기준으로 3방향 총알 쏘는 패턴
	if (m_dwTimer < GetTickCount() && (0 == (iRandomPattern % 3)) && (bPattern_A == false))
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP));
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN));
		m_dwTimer = (GetTickCount() + 1000);

		// 해당 bool변수가 true이면 다음 회전시 해당 패턴이 발생하지 않음
		bPattern_A = true;
		bPattern_B = false;
		bPattern_C = false;
	}

	/*	보스 기준, 맵 좌표 기준으로 나감
	// 패턴 A
	if (m_dwTimer < GetTickCount() && (0 == (iRandomPattern % 3)) && (bPattern_A == false))
	{
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(600, 100, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(620, 200, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(640, 300, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(660, 400, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(680, 500, DIR_LEFT));
	m_dwTimer = (GetTickCount() + 1000);

	bPattern_A = true;
	bPattern_B = false;
	bPattern_C = false;
	}

	// 패턴 B
	if (m_dwTimer < GetTickCount() && (1 == (iRandomPattern % 3)) && (bPattern_B == false))
	{
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(680, 100, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(660, 200, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(640, 300, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(620, 400, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(600, 500, DIR_LEFT));
	m_dwTimer = (GetTickCount() + 1000);

	bPattern_A = false;
	bPattern_B = true;
	bPattern_C = false;
	}

	// 패턴 C
	if (m_dwTimer < GetTickCount() && (2 == (iRandomPattern % 3)) && (bPattern_C == false))
	{
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(600, 100, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(570, 150, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(550, 200, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(540, 250, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(530, 300, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(540, 350, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(550, 400, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(570, 450, DIR_LEFT));
	m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(600, 500, DIR_LEFT));
	m_dwTimer = (GetTickCount() + 1000);

	bPattern_A = false;
	bPattern_B = false;
	bPattern_C = true;
	}
	*/

	// 평타
	if (m_dwTimer < GetTickCount())
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_dwTimer = GetTickCount() + 1000;

		bPattern_A = false;
		bPattern_B = false;
		bPattern_C = false;
	}
}


