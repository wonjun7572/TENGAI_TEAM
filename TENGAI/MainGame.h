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
	HDC				m_hDC;
	list<CObj*>		m_ObjList[OBJ_END];
	

	CScene*  m_SceneList;
	
	SCENE_NAME    m_eScene;
	int			 m_iPrevFlow;
	int			 m_iFlow;
	
	int			m_IEXIT;
	int			iScore ;
};