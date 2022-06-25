#pragma once
#include "Scene.h"
class CSecondScene :
	public CScene
{

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	LateUpdate(void);
	virtual int		Render(HDC hDC);
	virtual void	Release(void);



public:
	CSecondScene();
	virtual ~CSecondScene();
};

