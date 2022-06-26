#include "pch.h"
#include "SecondScene.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Item.h"
#include "CollisionMgr.h"
#include "Monster_Level_01.h"
#include "Monster_Level_02.h"
#include "Monster_Level_03.h"
#include "Monster_Level_04.h"
#include "Monster_Level_05.h"
#include "BossMonster.h"


CSecondScene::CSecondScene()
{

}


CSecondScene::~CSecondScene()
{
	Release();
}


void CSecondScene::Initialize(void)
{
	
//	m_ObjList[OBJ_PLAYER].front()->SetDead(false);
	m_ObjList[OBJ_PLAYER].front()->SetObjID(OBJ_PLAYER);

	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
	// 초기 몬스터 숫자 나중에 업데이트 문에서 추가해야될듯? 시간초마다
	for (int i = 0; i < 2; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_03>::Create(rand() % 500 + 100, rand() % 500 + 50));
	}
	// 몬스터 한마리마다 iterator 돌려서 Set_Bullet_Monster 해주므로써 몬스터도 총알 가지게 함
	for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
		dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
	}

	for (int i = 0; i < 1; ++i)
	{
		m_ObjList[OBJ_BOSSMONSTER].push_back(CAbstractFactory<CBossMonster>::Create());
	}

	for (auto& iter = m_ObjList[OBJ_BOSSMONSTER].begin(); iter != m_ObjList[OBJ_BOSSMONSTER].end(); ++iter)
	{
		dynamic_cast<CBossMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	}


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

			if (iEvent == OBJ_DEAD && i == OBJ_PLAYER)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
				return EXIT;
			
			}

			else if (iEvent == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
				if (i != OBJ_BULLET_PLAYER && i != OBJ_BULLET_MONSTER && i != OBJ_BULLET_BOSSMONSTER)
				{
					m_IScore += 1;
				}
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
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{

			obj->LateUpdate();
		}
	}

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PLAYER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOSSMONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_PLAYER], m_ObjList[OBJ_BOSSMONSTER]);

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_BOSSMONSTER]);

	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_BULLET_PLAYER], m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_PLAYER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_MONSTER]);
	CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_BOSSMONSTER]);


}

int CSecondScene::Render(HDC hDC)
{
	// 맵 2라는걸 알게하기위해서
	Ellipse(hDC, 200, 100, g_WindowRect.right, g_WindowRect.bottom);



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

	if (0 == m_ObjList[OBJ_MONSTER].size() && 0 == m_ObjList[OBJ_BOSSMONSTER].size())
	{
		if (m_dwTimer + 3000 < GetTickCount())
		{
			m_bStageClear = true;
		}
	}

	if (m_bStageClear)
	{
		return SCENE_NAME_FIRST;
	}

	else
	{
		return SCENE_NAME_SECOND;
	}


}

void CSecondScene::Release(void)
{
}

