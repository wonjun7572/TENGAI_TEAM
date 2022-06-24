#include "pch.h"
#include "MainGame.h"
#include "AbstractFactory.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "CollisionMgr.h"

CMainGame::CMainGame()
{
	// 변수 생성을 위한 srand 함수 생성
	srand(time(NULL));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	// 플레이어 충돌 시 하트 제거를 위해 아이디 값을 COBJ에 만듦
	m_ObjList[OBJ_PLAYER].front()->SetObjID(OBJ_PLAYER);
	
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);


	// 초기 몬스터 숫자 나중에 업데이트 문에서 추가해야될듯? 시간초마다
	for (int i = 0; i < 20; ++i)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(rand()%500+100,rand()%500 +50));
	
	}

	for (auto & iter : m_ObjList[OBJ_MONSTER])
	{
		dynamic_cast<CMonster*>(iter)->Set_ObjList(&m_ObjList[OBJ_ITEM]);
	}
}

void CMainGame::Update(void)
{

	for (int i = 0; i < OBJ_END; i++)
	{
		for (list<CObj*>::iterator iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();

			if (iEvent == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	

}

void CMainGame::LateUpdate(void)
{
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::CollisionSphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);

	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{
		
			obj->LateUpdate();
		}
	}

	

//	CCollisionMgr::CollisionRect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC,g_WindowRect.left , g_WindowRect.top, g_WindowRect.right , g_WindowRect.bottom);

	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{
			obj->Render(m_hDC);
		}
	}
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);
}
