#include "pch.h"
#include "FirstScene.h"
#include "AbstractFactory.h"

#include "Obj.h"
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

CFirstScene::~CFirstScene()
{
	Release();
}

void CFirstScene::Initialize(void)
{
	// �÷��̾� ����������� ����
	if(m_ObjList[OBJ_PLAYER].empty())
		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	
	
	// �÷��̾� �浹 �� ��Ʈ ���Ÿ� ���� ���̵� ���� COBJ�� ����
	m_ObjList[OBJ_PLAYER].front()->SetObjID(OBJ_PLAYER);

	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
	// �ʱ� ���� ���� ���߿� ������Ʈ ������ �߰��ؾߵɵ�? �ð��ʸ���
	for (int i = 0; i < 5; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster_Level_01>::Create(850, 100 + (i * 100)));
	}
	m_iStage = LEVEL_02;
	// ���� �Ѹ������� iterator ������ Set_Bullet_Monster ���ֹǷν� ���͵� �Ѿ� ������ ��
	for (auto& iter = m_ObjList[OBJ_MONSTER].begin(); iter != m_ObjList[OBJ_MONSTER].end(); ++iter)
	{
		dynamic_cast<CMonster*>(*iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_MONSTER]);
		dynamic_cast<CMonster*>(*iter)->Set_Bullet_Player(&m_ObjList[OBJ_BULLET_PLAYER]);
		dynamic_cast<CMonster*>(*iter)->Set_Player(&m_ObjList[OBJ_PLAYER]);
	}
	//for (int i = 0; i < 1; ++i)
	//{
	//	m_ObjList[OBJ_BOSSMONSTER].push_back(CAbstractFactory<CBossMonster>::Create());
	//}

	//for (auto& iter = m_ObjList[OBJ_BOSSMONSTER].begin(); iter != m_ObjList[OBJ_BOSSMONSTER].end(); ++iter)
	//{
	//	dynamic_cast<CBossMonster*>(*iter)->Set_Bullet_Monster(&m_ObjList[OBJ_BULLET_BOSSMONSTER]);
	//}

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
				// �÷��̾ �׾�����
				else if (i == OBJ_PLAYER && iEvent == OBJ_DEAD)
				{
					Safe_Delete<CObj*>(*iter);
					iter = m_ObjList[i].erase(iter);
					return 99;
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

		CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_PLAYER]);
		CCollisionMgr::CollisionWall(m_ObjList[OBJ_BULLET_MONSTER]);
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
	}



int CFirstScene::Render(HDC hDC)
{
	
		

		for (int i = 0; i < OBJ_END; i++)
		{
			for (auto& obj : m_ObjList[i])
			{
				obj->Render(hDC);
			}
		}

		// ���⼭ ���ͷ��� 5�� ����� 0�̸� ���� ���������� ���°� ������ ���ͼ��� 0�̸� Ŭ����
		if (0 == m_ObjList[OBJ_MONSTER].size() && 0 == m_ObjList[OBJ_BOSSMONSTER].size() && !m_ObjList[OBJ_PLAYER].empty())
		{
			switch (m_iStage)
			{
			case LEVEL_02:
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
				}
				break;
			case LEVEL_END:
				if (m_dwTimer + 3000 < GetTickCount())
				{
					m_bStageClear = true;
				}
				break;
			}

		}

		if (m_bStageClear)
		{
			return SCENE_NAME_SECOND;
		}

		else
		{
			return SCENE_NAME_FIRST;
		}
	
	


	
}
void CFirstScene::Release(void)
{
	
		for (int i = 0; i < OBJ_END; ++i)
		{
			for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
			m_ObjList[i].clear();
		}
	
}
