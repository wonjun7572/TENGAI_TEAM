#include "pch.h"
#include "MainGame.h"

#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "Scene.h"
#include "FirstScene.h"
#include "SecondScene.h"

CMainGame::CMainGame()
	: m_SceneList(nullptr)
{
	// 변수 생성을 위한 srand 함수 생성
	m_iFlow = 0;
	m_IEXIT = 0;
	iScore = 0;

	//sour = new list<CObj*>[8];
	

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	// 비어있을때만 생성하고 아니면 생성안하게 하고

	//m_ObjList = m_SceneList->Get_ObjList();
	m_SceneList = CAbstractFactory<CFirstScene>::Create_Scene();
}

	
	


void CMainGame::Update(void)
{
	if (m_IEXIT == EXIT)
		return;
	
	// 삭제하기 위해서 받아오기
	


	switch (m_iFlow)
	{
	case SCENE_NAME_FIRST:
		if (m_SceneList == nullptr)
		{
			m_SceneList= CAbstractFactory<CFirstScene>::Create_Scene(m_ObjList);

		}
	
		
	
		break;

	case SCENE_NAME_SECOND:
		
		if (m_SceneList == nullptr)
		{
			m_SceneList=  CAbstractFactory<CSecondScene>::Create_Scene(m_ObjList); 
			

		}

		
		break;
	default:
		break;
	}

	// 점수를 삭제하기 이전에 받아서 

	/*
	if (m_iFlow != m_iPrevFlow)
	{
		int RemoveScene = 0;
		for (auto iter = m_SceneList->begin(); iter != m_SceneList->end(); )
		{
			if (RemoveScene == m_iPrevFlow)
			{
				Safe_Delete<CScene*>(*iter);
				iter = m_SceneList->erase(iter);
				break;
			}
			else
			{
				++RemoveScene;
				++iter;
			}
		}
		m_SceneList[m_iPrevFlow].clear();
	}*/

	//Safe_Delete<CScene*>(m_SceneList);
	m_SceneList->Set_Score(iScore);
	m_IEXIT = m_SceneList->Update();
	//m_ObjList = m_SceneList->Get_ObjList();
	iScore = m_SceneList->Get_Score();
	// 현재에 넣어준다.
	
}



void CMainGame::LateUpdate(void)
{
	if (m_IEXIT == EXIT)
	{
		return;
	}

	m_SceneList->LateUpdate();
	
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, g_WindowRect.left, g_WindowRect.top, g_WindowRect.right, g_WindowRect.bottom);

	if (m_IEXIT == EXIT)
	{
		TCHAR		szBuff[32] = L"끝났습니다.";
		RECT	rc{ 400, 300, 800, 200 };
		RECT	rc2{ 600, 100, 800, 200 };
		
		TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));
		

		TCHAR		szBuff2[32] = L"";

		swprintf_s(szBuff2, L"SCORE :  %d", iScore);
		DrawText(m_hDC, szBuff2, lstrlen(szBuff2), &rc2, DT_CENTER);

		return;

	}

	m_iPrevFlow = m_iFlow;
	m_iFlow = m_SceneList->Render(m_hDC);
	
	

	if (m_iFlow != m_iPrevFlow)
	{
		for (int i = 0; i < OBJ_END; ++i)
		{
			m_ObjList[i].assign(m_SceneList->Get_ObjList()[i].begin(), (m_SceneList->Get_ObjList()[i].end()));
		}

		for (int i = 1; i < OBJ_END; ++i)
		{
			if (m_ObjList[i].size() == 0)
				m_ObjList[i].clear();
		}


		if (m_SceneList != nullptr)
		{
			++EEWEW;
			Safe_Delete<CScene*>(m_SceneList);
		}
	}
	
	
	
}
	


void CMainGame::Release(void)
{
	
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			Safe_Delete<CObj*>(*iter);
			iter = m_ObjList[i].erase(iter);

		}
	}

	
	Safe_Delete<CScene*>(m_SceneList);



	ReleaseDC(g_hWnd, m_hDC);
}
