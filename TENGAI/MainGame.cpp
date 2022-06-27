#include "pch.h"
#include "MainGame.h"

#include "AbstractFactory.h"
#include "CollisionMgr.h"

#include "Scene.h"
#include "FirstScene.h"
#include "SecondScene.h"

#include "Mouse.h"

CMainGame::CMainGame()
	: m_SceneList(nullptr)
{
	// ���� ������ ���� srand �Լ� ����
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
	m_hMemDC = GetDC(g_hWnd);

	m_mouse = new CMouse;
	m_mouse->Initialize();
	// ����������� �����ϰ� �ƴϸ� �������ϰ� �ϰ�

	//m_ObjList = m_SceneList->Get_ObjList();
	m_SceneList = CAbstractFactory<CFirstScene>::Create_Scene();
}

void CMainGame::Update(void)
{
	if (m_IEXIT == EXIT)
		return;
	
	// �����ϱ� ���ؼ� �޾ƿ���
	


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

	// ������ �����ϱ� ������ �޾Ƽ� 

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
	// ���翡 �־��ش�.
	
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

	// ���� �� �κ� Ending Scene ���� �־������.
	if (m_IEXIT == EXIT)
	{
		m_hDC = CreateCompatibleDC(m_hMemDC);
		m_bitBack = CreateCompatibleBitmap(m_hMemDC, g_WindowRect.right, g_WindowRect.bottom);
		m_bitOldBack = (HBITMAP)SelectObject(m_hDC, m_bitBack);
		PatBlt(m_hDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, WHITENESS);
		Ellipse(m_hDC, 200, 100, g_WindowRect.right, g_WindowRect.bottom);


		m_mouse->Update();
		m_mouse->Render(m_hDC);

		if (m_mouse->GetRect().left >= 200 &&
			m_mouse->GetRect().right <= g_WindowRect.right &&
			m_mouse->GetRect().top >= 100 &&
			m_mouse->GetRect().bottom <= g_WindowRect.bottom)
		{
			//���콺 �浹 �ǰ������� render �ٲ��ְ� set�Լ� �ϳ� ������ֱ�.
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				int a = 0;
				// ���� ��ư ����� ����� ��.
			}
		}

		TCHAR		szBuff[32] = L"�������ϴ�.";
		RECT	rc{ 400, 300, 800, 200 };
		RECT	rc2{ 600, 100, 800, 200 };

		TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));

		TCHAR		szBuff2[32] = L"";

		swprintf_s(szBuff2, L"SCORE :  %d", iScore);
		DrawText(m_hDC, szBuff2, lstrlen(szBuff2), &rc2, DT_CENTER);

		BitBlt(m_hMemDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, m_hDC, 0, 0, SRCCOPY);
		SelectObject(m_hDC, m_bitOldBack);
		DeleteObject(m_bitBack);
		return;
	}

	m_hDC = CreateCompatibleDC(m_hMemDC);
	m_bitBack = CreateCompatibleBitmap(m_hMemDC, g_WindowRect.right, g_WindowRect.bottom);
	m_bitOldBack = (HBITMAP)SelectObject(m_hDC, m_bitBack);
	PatBlt(m_hDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, WHITENESS);

	m_iPrevFlow = m_iFlow;
	m_iFlow = m_SceneList->Render(m_hDC);
	
	if (m_iFlow != m_iPrevFlow)
	{
		for (int i = 0; i < OBJ_END; ++i)
		{
			m_ObjList[i].assign(m_SceneList->Get_ObjList()[i].begin(), (m_SceneList->Get_ObjList()[i].end()));
		}

		for (int i = 1; i <= OBJ_BOSSMONSTER2; ++i)
		{
			if (m_ObjList[i].size() == 0)
				for (auto& iter : m_ObjList[i])
				{
					Safe_Delete<CObj*>(iter);
				}
				m_ObjList[i].clear();
		}


		if (m_SceneList != nullptr)
		{
			++EEWEW;
			Safe_Delete<CScene*>(m_SceneList);
		}
	}
	
	BitBlt(m_hMemDC, 0, 0, g_WindowRect.right, g_WindowRect.bottom, m_hDC, 0, 0, SRCCOPY);
	SelectObject(m_hDC, m_bitOldBack);
	DeleteObject(m_bitBack);
	
}
	


void CMainGame::Release(void)
{
	
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
