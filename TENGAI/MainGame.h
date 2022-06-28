#pragma once
#include "Include.h"

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

	bool		GetQuit() { return m_bQuit; }

private:
	HDC				m_hDC;
	HDC				m_hMemDC;

	HBITMAP			m_bitBack;
	HBITMAP			m_bitOldBack;
	
	list<CObj*>		m_ObjList[OBJ_END];
	CObj*			m_mouse;
	CScene*			m_SceneList;
	
	SCENE_NAME		m_eScene;

	int				m_iPrevFlow;
	int				m_iFlow;
	int				m_iEXIT;
	int				m_iScore;
	bool			m_bQuit;
};