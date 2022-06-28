#include "pch.h"
#include "SecondScene.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Item.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "Monster_Level_01.h"
#include "Monster_Level_02.h"
#include "Monster_Level_03.h"
#include "Monster_Level_04.h"
#include "Monster_Level_05.h"
#include "Pet.h"
#include "BossMonster2.h"

CSecondScene::CSecondScene()
{
}

CSecondScene::CSecondScene(list<CObj*>* temp)
	:CScene(temp)
{
	m_bStageClear = false;
}

CSecondScene::~CSecondScene()
{
	Release();
}

void CSecondScene::Initialize(void)
{
	for (int i = 0; i < 5; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_01>::Create(850, 100 + (i * 100), DIR_END, OBJ_MONSTER));
	}

	for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_SHIELD]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PET]);
		dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
		dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
	}
	m_iStage = LEVEL_02;
	m_dwTimer = GetTickCount();
}

int CSecondScene::Update(void)
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
	return SCENE_NAME_SECOND;
}

void CSecondScene::LateUpdate(void)
{
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

	//CCollisionMgr::CollisionSphere(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_BULLET_MONSTER]);
	//CCollisionMgr::CollisionSphere(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_BULLET_BOSSMONSTER]);

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_SHIELD], m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_SHIELD], m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_SHIELD], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_SHIELD], m_ObjList[OBJ_BOSSMONSTER]);

	CCollisionMgr::CollisionWall2(m_ObjList[OBJ_BULLET_PLAYER]);
	CCollisionMgr::CollisionWall2(m_ObjList[OBJ_BULLET_PET]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BOSSMONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);


	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{
			obj->LateUpdate();
		}
	}

	if (0 == m_ObjList[OBJ_MONSTER].size() && 0 == m_ObjList[OBJ_BOSSMONSTER].size())
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
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_SHIELD]);
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
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_SHIELD]);
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
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_SHIELD]);
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
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_SHIELD]);
				dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			break;
		case LEVEL_BOSS:
			m_iStage = LEVEL_END;

			m_ObjList[OBJ_BOSSMONSTER].push_back(CAbstractFactory<CBossMonster2>::Create(850, 300, DIR_END, OBJ_BOSSMONSTER));
			for (auto& iter = m_ObjList[OBJ_BOSSMONSTER].begin(); iter != m_ObjList[OBJ_BOSSMONSTER].end(); ++iter)
			{
				dynamic_cast<CBossMonster2*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_BOSSMONSTER]);
				dynamic_cast<CBossMonster2*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CBossMonster2*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_SHIELD]);
				dynamic_cast<CBossMonster2*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CBossMonster2*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			break;

		case LEVEL_END:
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

int CSecondScene::Render(HDC hDC)
{
	HBRUSH hNewBrush = CreateSolidBrush(RGB(0x99, 0x32, 0xcc));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC,hNewBrush);
	Rectangle(hDC, 0, 0, 800, 400);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hNewBrush);

	HBRUSH hNewBrush2 = CreateSolidBrush(RGB(0x8b, 0x4f, 0x1d));
	HBRUSH hOldBrush2 = (HBRUSH)SelectObject(hDC, hNewBrush2);
	Rectangle(hDC, 0, 400, 800, 600);
	SelectObject(hDC, hOldBrush2);
	DeleteObject(hNewBrush2);

	TCHAR		szBuff1[32] = L"";
	RECT	rc1{ 300, 50, 500, 150 };
	swprintf_s(szBuff1, L"STAGE 2");
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
		for (int i = OBJ_MONSTER; i <= OBJ_BULLET_BOSSMONSTER; ++i)
		{
			for (list<CObj*>::iterator iter = m_ObjList[i].begin();
				iter != m_ObjList[i].end();)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);

			}
		}
		return SCENE_NAME_ENDDING;
	}
	else
	{
		return SCENE_NAME_SECOND;
	}
}

void CSecondScene::Release(void)
{
}