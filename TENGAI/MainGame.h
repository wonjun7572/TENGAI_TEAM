#pragma once

#include "Include.h"
//#include "../Header/Include.h"

class CObj;
class CScene;

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
	list<CObj*> *	m_ObjList;
	list<CScene*> m_SceneList[SCENE_NAME_END];
	
	SCENE_NAME    m_eScene;
	int			 m_iFlow;
	
	int			m_count = 0;
};