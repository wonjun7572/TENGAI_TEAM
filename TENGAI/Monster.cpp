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
	// ������ ����
	// ������ ������ ������ �ƴϰ� �������� ����
	m_pItem->push_back(CAbstractFactory<CAddHpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	for (auto& iter = m_pItem->begin(); iter != m_pItem->end(); ++iter)
	{
		dynamic_cast<CAddHpItem*>(*iter)->SetPlayer(m_pPlayer->front());
	}
}

void CMonster::Attack()		// ���� �̻��� �߻� �ڵ�, GetTickCount() + ���ϴ� �ð��� �Է�
{
	// �������� ���� ����� ���� 0~99���� ���� �Ź� �����ϰ� �������� ��
	srand((unsigned int)time(nullptr) + GetTickCount());
	int iRandomPattern = rand() % 99;

	// ���� �������� 3���� �Ѿ� ��� ����
	if (m_dwTimer < GetTickCount() && (0 == (iRandomPattern % 3)) && (bPattern_A == false))
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTUP));
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFTDOWN));
		m_dwTimer = (GetTickCount() + 1000);

		// �ش� bool������ true�̸� ���� ȸ���� �ش� ������ �߻����� ����
		bPattern_A = true;
		bPattern_B = false;
		bPattern_C = false;
	}

	/*	���� ����, �� ��ǥ �������� ����
	// ���� A
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

	// ���� B
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

	// ���� C
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

	// ��Ÿ
	if (m_dwTimer < GetTickCount())
	{
		m_pBullet_Monster->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		m_dwTimer = GetTickCount() + 1000;

		bPattern_A = false;
		bPattern_B = false;
		bPattern_C = false;
	}
}


