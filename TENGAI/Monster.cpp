#include "pch.h"
#include "Monster.h"
#include "Item.h"
#include "Bullet.h"
#include "AddHpItem.h"
#include "AddPowerUpItem.h"
#include "AddUltimateItem.h"
#include "AddPetPowerUp.h"

CMonster::CMonster()
	:iReverse(1), m_pBullet_Player(nullptr), m_pBullet_Monster(nullptr), m_pItem(nullptr)
{
}

CMonster::~CMonster()
{
}

void CMonster::CreateItem()
{
	int iRand = rand() % 4;
	if (rand() % 4 == 0)
	{
		m_pItem->push_back(CAbstractFactory<CAddHpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	}
	else if (rand() % 4 == 1)
	{
		m_pItem->push_back(CAbstractFactory<CAddPowerUpItem>::Create(m_tInfo.fX, m_tInfo.fY));
	}
	else if (rand() % 4 == 2)
	{
		m_pItem->push_back(CAbstractFactory<CAddUltimateItem>::Create(m_tInfo.fX, m_tInfo.fY));
	}
	else if (rand() % 4 == 3)
	{
		m_pItem->push_back(CAbstractFactory<CAddPetPowerUp>::Create(m_tInfo.fX, m_tInfo.fY));
	}

	for (auto& iter = m_pItem->begin(); iter != m_pItem->end(); ++iter)
	{
		dynamic_cast<CItem*>(*iter)->SetPlayer(m_pPlayer->front());
		dynamic_cast<CItem*>(*iter)->SetPet(m_pPet->front());
	}
}