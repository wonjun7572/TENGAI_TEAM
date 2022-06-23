#pragma once

#include "Include.h"
//#include "../Header/Include.h"

class CObj;

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
};