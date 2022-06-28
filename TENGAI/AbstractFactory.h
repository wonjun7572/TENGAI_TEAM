#pragma once

#include "Obj.h"
#include "Scene.h"
#include "Monster.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, DIR _dir=DIR_END ,OBJID _ID = OBJ_END)
	{
		CObj* pObj = new T;
		pObj->SetObjID(_ID);
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY, _dir);
		return pObj;
	}

	static CObj* Create_ChaseBullet(float _fX, float _fY, float _fCos, float _fSin, DIR _dir = DIR_END, OBJID _ID = OBJ_END)
	{
		CObj* pObj = new T;
		pObj->SetObjID(_ID);
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY, _dir, _fCos, _fSin);
		return pObj;
	}

	static CScene* Create_Scene()
	{
		CScene* pScene = new T;
		pScene->Initialize();
		return pScene;

	}

	static CScene* Create_Scene(list<CObj*>* temp )
	{
		CScene* pScene = new T(temp);
		pScene->Initialize();

		return pScene;
	}

	CAbstractFactory() {}

	~CAbstractFactory() {}
};

