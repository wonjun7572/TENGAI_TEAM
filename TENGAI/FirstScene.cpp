#include "pch.h"
#include "FirstScene.h"
#include "AbstractFactory.h"

#include "Obj.h"
#include "Pet.h"
#include "Player.h"
#include "Monster.h"
#include "Monster_Level_01.h"
#include "Monster_Level_02.h"
#include "Monster_Level_03.h"
#include "Monster_Level_04.h"
#include "Monster_Level_05.h"
#include "BossMonster.h"
#include "Bullet.h"
#include "Item.h"
#include "CollisionMgr.h"

CFirstScene::CFirstScene()
{
	srand((unsigned int)time(NULL));
}

CFirstScene::CFirstScene(list<CObj*> *temp)
	:CScene(temp)
{
}

CFirstScene::~CFirstScene()
{
	Release();
}

void CFirstScene::Initialize(void)
{
	if (m_ObjList[OBJ_PLAYER].empty())
	{
		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create(OBJ_PLAYER));
		m_ObjList[OBJ_PLAYER].front()->SetObjID(OBJ_PLAYER);
		m_ObjList[OBJ_PET].push_back(CAbstractFactory<CPet>::Create(OBJ_PET));

		dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
		dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
		dynamic_cast<CPet*>(m_ObjList[OBJ_PET].front())->Set_Bullet_Pet(&m_ObjList[OBJ_BULLET_PET]);
		dynamic_cast<CPet*>(m_ObjList[OBJ_PET].front())->Set_Player(&m_ObjList[OBJ_PLAYER]);
		//////////////////////////////////////////////////////변경////////////////////////////////////////////////////////
		dynamic_cast<CPet*>(m_ObjList[OBJ_PET].front())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
		dynamic_cast<CPet*>(m_ObjList[OBJ_PET].front())->Set_BossMonster(&m_ObjList[OBJ_BOSSMONSTER]);
		//////////////////////////////////////////////////////변경////////////////////////////////////////////////////////
	}

	for (int i = 0; i < 5; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_01>::Create(850, 100 + (i * 100), DIR_END, OBJ_MONSTER));
	}

	for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Pet(&m_ObjList[OBJ_BULLET_PET]);
		dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
		dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
	}
	m_iStage = LEVEL_02;
	m_dwTimer = GetTickCount();
}

int CFirstScene::Update(void)
{
	if (!m_ObjList[OBJ_PLAYER].empty())
	{
		for (int i = 0; i < OBJ_END; i++)
		{
			for (list<CObj*>::iterator iter = m_ObjList[i].begin();
				iter != m_ObjList[i].end();)
			{

				int iEvent = (*iter)->Update();

				if (iEvent == OBJ_DEAD && i != OBJ_PLAYER)
				{
					Safe_Delete<CObj*>(*iter);
					iter = m_ObjList[i].erase(iter);
				}
				else if (i == OBJ_PLAYER && iEvent == OBJ_DEAD)
				{
					Safe_Delete<CObj*>(*iter);
					iter = m_ObjList[i].erase(iter);
					return EXIT;
				}
				else
				{
					iter++;
				}
			}
		}
	}
	return 0;
}

void CFirstScene::LateUpdate(void)
{
	/*
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PLAYER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOSSMONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_PLAYER], m_ObjList[OBJ_BOSSMONSTER]);

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_BOSSMONSTER]);

	CCollisionMgr::CollisionWall2(m_ObjList[OBJ_BULLET_PLAYER]);
	CCollisionMgr::CollisionWall2(m_ObjList[OBJ_BULLET_PET]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BOSSMONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	*/

	if (SCORE_PLUS == CCollisionMgr::CollisionSphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PLAYER]))
	{
		m_IScore += 1;
	}
	if (SCORE_PLUS == CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BOSSMONSTER], m_ObjList[OBJ_BULLET_PLAYER]))
	{
		m_IScore += 1;
	}

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PET]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BOSSMONSTER], m_ObjList[OBJ_BULLET_PET]);

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOSSMONSTER]);

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_BOSSMONSTER]);

	CCollisionMgr::CollisionWall2(m_ObjList[OBJ_BULLET_PLAYER]);
	CCollisionMgr::CollisionWall2(m_ObjList[OBJ_BULLET_PET]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BOSSMONSTER]);
	//CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);

	
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{
			obj->LateUpdate();
		}
	}

	if (0 == m_ObjList[OBJ_MONSTER].size() && 0 == m_ObjList[OBJ_BOSSMONSTER].size() && !m_ObjList[OBJ_PLAYER].empty())
	{
		switch (m_iStage)
		{
		case LEVEL_02:
			m_iStage = LEVEL_03;
			for (int i = 0; i < 5; ++i)
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_02>::Create(850, 100 + (i * 100), DIR_END, OBJ_MONSTER));
			}
			for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
			{
				dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}

			break;
		case LEVEL_03:
			m_iStage = LEVEL_04;
			for (int i = 0; i < 5; ++i)
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_03>::Create(850, 100 + (i * 100), DIR_END, OBJ_MONSTER));
			}
			for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
			{
				dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			break;
		case LEVEL_04:
			m_iStage = LEVEL_05;
			for (int i = 0; i < 5; ++i)
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_04>::Create(850, 100 + (i * 100), DIR_END, OBJ_MONSTER));
			}
			for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
			{
				dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			break;
		case LEVEL_05:
			m_iStage = LEVEL_BOSS;

			for (int i = 0; i < 5; ++i)
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_05>::Create(850, 100 + (i * 100), DIR_END, OBJ_MONSTER));
			}
			for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
			{
				dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			break;
		case LEVEL_BOSS:
			m_iStage = LEVEL_END;

			m_ObjList[OBJ_BOSSMONSTER].push_back(CAbstractFactory<CBossMonster>::Create(550, 50, DIR_END, OBJ_BOSSMONSTER));
			for (auto& iter = m_ObjList[OBJ_BOSSMONSTER].begin(); iter != m_ObjList[OBJ_BOSSMONSTER].end(); ++iter)
			{
				dynamic_cast<CBossMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_BOSSMONSTER]);
				dynamic_cast<CBossMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CBossMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CBossMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			break;
		case LEVEL_END:
				//m_bStageClear = true;
			if (true == m_bFinish)
			{
				m_dwTimer = GetTickCount();
				m_bFinish = false;
			}

			if (false == m_bFinish)
			{
				if (m_dwTimer + 3000 < GetTickCount())
					m_bStageClear = true;
			}

			break;
		}
	}
}

int CFirstScene::Render(HDC hDC)
{
	HBRUSH hNewBrush = CreateSolidBrush(RGB(0x5c, 0xee, 0xe6));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
	hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
	Rectangle(hDC, 0, 0, 800, 400);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);

	HBRUSH hNewBrush2 = CreateSolidBrush(RGB(0x0a, 0x6e, 0x0a));
	HBRUSH hOldBrush2 = (HBRUSH)SelectObject(hDC, hNewBrush2);
	Rectangle(hDC, 0, 400, 800, 600);
	SelectObject(hDC, hOldBrush2);
	DeleteObject(hNewBrush2);


	HBRUSH hNewBrush3 = CreateSolidBrush(RGB(0xe5, 0x6d, 0x29));
	HBRUSH hOldBrush3 = (HBRUSH)SelectObject(hDC, hNewBrush3);
	Ellipse(hDC, 450, 50, 600, 200);
	SelectObject(hDC, hOldBrush3);
	DeleteObject(hNewBrush3);


	TCHAR		szBuff1[32] = L"";
	RECT	rc1{ 300, 50, 500, 150 };
	swprintf_s(szBuff1, L"STAGE 1");
	DrawText(hDC, szBuff1, lstrlen(szBuff1), &rc1, DT_CENTER);

	TCHAR		szBuff2[32] = L"";
	RECT	rc2{ 600, 100, 800, 200 };
	swprintf_s(szBuff2, L"SCORE :  %d", m_IScore);
	DrawText(hDC, szBuff2, lstrlen(szBuff2), &rc2, DT_CENTER);
		
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{
			obj->Render(hDC);
		}
	}

	if (m_bStageClear)
	{
		for (int i = OBJ_MONSTER; i <= OBJ_BULLET_BOSSMONSTER2; ++i)
		{
			for (list<CObj*>::iterator iter = m_ObjList[i].begin();
				iter != m_ObjList[i].end();)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
		}
		return SCENE_NAME_SECOND;
	}
	else
	{
		return SCENE_NAME_FIRST;
	}
}

void CFirstScene::Release(void)
{	
}
