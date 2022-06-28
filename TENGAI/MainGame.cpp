#include "pch.h"
#include "MainGame.h"

#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "Scene.h"
#include "FirstScene.h"
#include "SecondScene.h"

#include "Mouse.h"

CMainGame::CMainGame()
	: m_SceneList(nullptr), m_bQuit(false), m_iFlow(0), m_iEXIT(0), m_iScore(0)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	m_hMemDC = GetDC(g_hWnd);

	m_hDC = CreateCompatibleDC(m_hMemDC);
	m_bitBack = CreateCompatibleBitmap(m_hMemDC, g_WindowRect.right, g_WindowRect.bottom);

	m_mouse = new CMouse;
	m_mouse->Initialize();

	m_SceneList = CAbstractFactory<CFirstScene>::Create_Scene();
}

void CMainGame::Update(void)
{
	if (m_iEXIT == EXIT)
		return;

	switch (m_iFlow)
	{
	case SCENE_NAME_FIRST:
		if (m_SceneList == nullptr)
			m_SceneList = CAbstractFactory<CFirstScene>::Create_Scene(m_ObjList);
		break;

	case SCENE_NAME_SECOND:
		if (m_SceneList == nullptr)
			m_SceneList = CAbstractFactory<CSecondScene>::Create_Scene(m_ObjList);
		break;

	case SCENE_NAME_ENDDING:
		m_iEXIT = EXIT;
		return;

	default:
		break;
	}
	m_SceneList->Set_Score(m_iScore);
	m_iEXIT = m_SceneList->Update();
}

void CMainGame::LateUpdate(void)
{
	if (m_iEXIT == EXIT)
		return;

	m_SceneList->LateUpdate();
}

void CMainGame::Render(void)
{
	// 종료처리
	if (m_iEXIT == EXIT)
	{
		m_bitOldBack = (HBITMAP)SelectObject(m_hDC, m_bitBack);
		PatBlt(m_hDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, WHITENESS);

		Rectangle(m_hDC, 400, 400, 600, 500);
		TCHAR		szBuff3[32] = L"종료하기";

		TextOut(m_hDC, 465, 445, szBuff3, lstrlen(szBuff3));

		m_mouse->Update();
		m_mouse->Render(m_hDC);

		if (m_mouse->GetRect().left >= 400 &&
			m_mouse->GetRect().right <= 600 &&
			m_mouse->GetRect().top >= 400 &&
			m_mouse->GetRect().bottom <= 500)
		{
			dynamic_cast<CMouse*>(m_mouse)->SetTrue();
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				m_bQuit = true;
				return;
			}
		}
		else
			dynamic_cast<CMouse*>(m_mouse)->SetFalse();

		TCHAR		szBuff[32] = L"끝났습니다.";
		RECT	rc{ 400, 300, 800, 200 };
		RECT	rc2{ 600, 100, 800, 200 };

		TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));

		TCHAR		szBuff2[32] = L"";

		swprintf_s(szBuff2, L"SCORE :  %d", m_iScore);
		DrawText(m_hDC, szBuff2, lstrlen(szBuff2), &rc2, DT_CENTER);

		BitBlt(m_hMemDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, m_hDC, 0, 0, SRCCOPY);
		SelectObject(m_hDC, m_bitOldBack);
		return;
	}

	m_bitOldBack = (HBITMAP)SelectObject(m_hDC, m_bitBack);
	PatBlt(m_hDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, WHITENESS);

	m_iPrevFlow = m_iFlow;
	m_iFlow = m_SceneList->Render(m_hDC);

	m_iScore = m_SceneList->Get_Score();

	if (m_iFlow != m_iPrevFlow)
	{
		for (int i = 0; i < OBJ_END; ++i)
		{
			m_ObjList[i].assign(m_SceneList->Get_ObjList()[i].begin(), (m_SceneList->Get_ObjList()[i].end()));
		}

		for (int i = 1; i <= OBJ_BOSSMONSTER2; ++i)
		{
			for (auto& iter : m_ObjList[i])
			{
				Safe_Delete<CObj*>(iter);
			}
			m_ObjList[i].clear();
		}

		if (m_SceneList != nullptr)
		{
			Safe_Delete<CScene*>(m_SceneList);
		}
	}

	BitBlt(m_hMemDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, m_hDC, 0, 0, SRCCOPY);
	SelectObject(m_hDC, m_bitOldBack);
}

void CMainGame::Release(void)
{
	DeleteObject(m_bitBack);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			iter = m_ObjList[i].erase(iter);
		}
		m_ObjList[i].clear();
	}

	m_ObjList->clear();

	Safe_Delete<CScene*>(m_SceneList);

	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hMemDC);
}
