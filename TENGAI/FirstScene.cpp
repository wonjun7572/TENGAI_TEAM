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
	// 플레이어 비어있을떄만 생성
	if (m_ObjList[OBJ_PLAYER].empty())
	{
		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());


		// 플레이어 충돌 시 하트 제거를 위해 아이디 값을 COBJ에 만듦
		m_ObjList[OBJ_PLAYER].front()->SetObjID(OBJ_PLAYER);
		m_ObjList[OBJ_PET].push_back(CAbstractFactory<CPet>::Create());

		dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
		dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
		dynamic_cast<CPet*>(m_ObjList[OBJ_PET].front())->Set_Bullet_Pet(&m_ObjList[OBJ_BULLET_PET]);
		dynamic_cast<CPet*>(m_ObjList[OBJ_PET].front())->Set_Player(&m_ObjList[OBJ_PLAYER]);
	}
	// 초기 몬스터 숫자 나중에 업데이트 문에서 추가해야될듯? 시간초마다
	for (int i = 0; i < 5; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_01>::Create(850, 100 + (i * 100)));
	}
	// 몬스터 한마리마다 iterator 돌려서 Set_Bullet_Monster 해주므로써 몬스터도 총알 가지게 함
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
	//m_iStage = LEVEL_END;
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
					//if (i != OBJ_BULLET_PLAYER && i !=OBJ_BULLET_MONSTER && i!=OBJ_BULLET_BOSSMONSTER)
					//{
					//	m_IScore += 1;
					//}
					
				}
				// 플레이어가 죽었을떄
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
			//m_iStage = LEVEL_03;
			m_iStage = LEVEL_03;
			for (int i = 0; i < 5; ++i)
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_02>::Create(850, 100 + (i * 100)));
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
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_03>::Create(850, 100 + (i * 100)));
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
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_04>::Create(850, 100 + (i * 100)));
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
			m_iStage = LEVEL_END;

			for (int i = 0; i < 5; ++i)
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_05>::Create(850, 100 + (i * 100)));
			}
			for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
			{
				dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
				dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
				dynamic_cast<CMonster*>(*iter)->Set_Pet(&m_ObjList[OBJ_PET]);
			}
			m_dwTimer = GetTickCount();
			break;
		case LEVEL_END:

			//if (0 == m_ObjList[OBJ_MONSTER].size() && 0 == m_ObjList[OBJ_BOSSMONSTER].size())
			//{

			//}
			/*if (m_dwTimer + 15000 < GetTickCount())
			{*/
				m_bStageClear = true;
			//}
			break;
		}

	}

	// 보스 잡은 후 겟틱을 수정해야된다.
}

int CFirstScene::Render(HDC hDC)
{
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
		//총알 들과 몬스터 싹다 정리
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
