#pragma once

#include "Obj.h"

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

	static CObj* Create(float _fX, float _fY, DIR _dir)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY, _dir);
		pObj->Initialize();

		return pObj;
	}

	CAbstractFactory() {}

	~CAbstractFactory() {}
};

