#include "pch.h"
#include "SecondScene.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Item.h"
#include "CollisionMgr.h"

void CSecondScene::Initialize(void)
{


}

int CSecondScene::Update(void)
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

}

int CSecondScene::Render(HDC hDC)
{
	Rectangle(hDC, g_WindowRect.left, g_WindowRect.top, g_WindowRect.right, g_WindowRect.bottom);

	Ellipse(hDC, 200, 100, g_WindowRect.right, g_WindowRect.bottom);



	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto& obj : m_ObjList[i])
		{
			obj->Render(hDC);
		}
	}

	return SCENE_NAME_SECOND;

}

void CSecondScene::Release(void)
{
}

CSecondScene::CSecondScene()
{
}


CSecondScene::~CSecondScene()
{
}
