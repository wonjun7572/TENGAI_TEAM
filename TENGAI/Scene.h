#pragma once
#include "Include.h"

class CObj;

class CScene
{
public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	LateUpdate(void)	PURE;
	virtual int		Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	list<CObj*>*			Get_ObjList() { return m_ObjList; }

	const bool			GetStageClear() const { return m_bStageClear; }
	void				SetStageClear(bool _bStageClear) { m_bStageClear = _bStageClear; }

public:
	const int		Get_Score() { return m_IScore; }
	void			Set_Score(int _iScore) { m_IScore = _iScore; }

public:
	CScene();
	CScene(list<CObj*>* temp);
	virtual ~CScene();

protected:
	int				m_IScore;

protected:
	list<CObj*>		m_ObjList[OBJ_END];
	DWORD			m_dwTimer;
	bool			m_bStageClear;
	int				m_iStage;
	bool			m_bStageEmptyCheck;
};

