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
	m_IEXIT = 0;
	iScore = 0;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	m_hMemDC = GetDC(g_hWnd);

	// 비어있을때만 생성하고 아니면 생성안하게 하고
	m_SceneList[SCENE_NAME_FIRST].push_back(CAbstractFactory<CFirstScene>::Create_Scene());
	m_ObjList = m_SceneList[m_iFlow].front()->Get_ObjList();
}

void CMainGame::Update(void)
{
	if (m_IEXIT == EXIT)
		return;

	switch (m_iFlow)
	{
	case SCENE_NAME_FIRST:
		
		if (m_SceneList[SCENE_NAME_FIRST].empty())
		{
			m_SceneList[SCENE_NAME_FIRST].push_back(CAbstractFactory<CFirstScene>::Create_Scene(*m_ObjList));
		}

		break;

	case SCENE_NAME_SECOND:
		
		if (m_SceneList[SCENE_NAME_SECOND].empty())
		{
			m_SceneList[SCENE_NAME_SECOND].push_back(CAbstractFactory<CSecondScene>::Create_Scene(*m_ObjList));
		}

		break;
	default:
		break;
	}
	// 점수를 삭제하기 이전에 받아서 
	iScore = m_SceneList[m_iPrevFlow].front()->Get_Score();
	// 현재에 넣어준다.
	m_SceneList[m_iFlow].front()->Set_Score(iScore);
	
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
	}

	m_IEXIT = m_SceneList[m_iFlow].front()->Update();
}

void CMainGame::LateUpdate(void)
{
	if (m_IEXIT == EXIT)
	{
		return;
	}

	m_SceneList[m_iFlow].front()->LateUpdate();
	
}

void CMainGame::Render(void)
{
	m_hDC = CreateCompatibleDC(m_hMemDC);
	m_bitBack = CreateCompatibleBitmap(m_hMemDC, g_WindowRect.right, g_WindowRect.bottom);
	m_bitOldBack = (HBITMAP)SelectObject(m_hDC, m_bitBack);
	PatBlt(m_hDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, WHITENESS);

	Rectangle(m_hDC, g_WindowRect.left, g_WindowRect.top, g_WindowRect.right, g_WindowRect.bottom);
	
	// 지금 이 부분 Ending Scene 만들어서 넣어줘야함.
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
	m_iFlow = m_SceneList[m_iPrevFlow].front()->Render(m_hDC);
	m_ObjList = m_SceneList[m_iPrevFlow].front()->Get_ObjList();
	BitBlt(m_hMemDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, m_hDC, 0, 0, SRCCOPY);
	SelectObject(m_hDC, m_bitOldBack);
	DeleteObject(m_bitBack);
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
	
	for (int i = 0; i < SCENE_NAME_END; ++i)
	{
		for_each(m_SceneList[i].begin(), m_SceneList[i].end(), Safe_Delete<CScene*>);
		m_SceneList[i].clear();
	}

	ReleaseDC(g_hWnd, m_hDC);
}
