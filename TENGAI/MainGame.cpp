#include "pch.h"
#include "MainGame.h"

#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "Scene.h"
#include "FirstScene.h"
#include "SecondScene.h"

CMainGame::CMainGame()
	:m_ObjList(nullptr)
{
	// 변수 생성을 위한 srand 함수 생성
	m_iFlow = 0;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	
	// 비어있을때만 생성하고 아니면 생성안하게 하고
	m_SceneList[SCENE_NAME_FIRST].push_back(CAbstractFactory<CFirstScene>::Create_Scene());
	m_ObjList = m_SceneList[m_iFlow].front()->Get_ObjList();
	
	
}

void CMainGame::Update(void)
{


	switch (m_iFlow)
	{
	case SCENE_NAME_FIRST:
		if (m_SceneList[SCENE_NAME_FIRST].empty())
		{
			m_SceneList[SCENE_NAME_FIRST].push_back(CAbstractFactory<CSecondScene>::Create_Scene(*m_ObjList));
			m_ObjList = m_SceneList[m_iFlow].front()->Get_ObjList();
		}
	
		break;
	
	case SCENE_NAME_SECOND:
		if (m_SceneList[SCENE_NAME_SECOND].empty())
		{
			m_SceneList[SCENE_NAME_SECOND].push_back(CAbstractFactory<CSecondScene>::Create_Scene(*m_ObjList));
			m_ObjList = m_SceneList[m_iFlow].front()->Get_ObjList();
		}
		
		break;
	default:
		break;
	}

	m_SceneList[m_iFlow].front()->Update();

	//m_iFlow = m_SceneList[SCENE_NAME_SECOND].front()->Update();

	if (m_count > 5)
	{
		m_count++;
	}

}

void CMainGame::LateUpdate(void)
{
	m_SceneList[m_iFlow].front()->LateUpdate();
	
}

void CMainGame::Render(void)
{
	int			 m_iTemp	= m_iFlow;
	m_iFlow = m_SceneList[m_iTemp].front()->Render(m_hDC);

	if (m_iFlow != m_iTemp)
	{
		for (auto iter= m_SceneList->begin(); iter!= m_SceneList->end(); )
		{
			//Safe_Delete<CScene*>(*iter);
			iter = m_SceneList->erase(iter);
			m_count++;
		}
	
		m_SceneList[m_iTemp].clear();
			
	}

	// 


}

void CMainGame::Release(void)
{

	

	ReleaseDC(g_hWnd, m_hDC);
}
