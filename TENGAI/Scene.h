#pragma once
#include "Include.h"

class CObj;


class CScene
{


public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	LateUpdate(void)	PURE;
	virtual int	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	list<CObj*>*	Get_ObjList() { return m_ObjList; }
	void			Set_ObjList(list<CObj*> temp) 
	{
		*m_ObjList = temp;

	}

public:
	CScene();
	virtual ~CScene();


protected:
	list<CObj*>		m_ObjList[OBJ_END];

	bool			m_bStageClear = false;

};

