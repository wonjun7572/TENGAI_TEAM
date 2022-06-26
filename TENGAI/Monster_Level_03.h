#pragma once
#include "Monster.h"
class CMonster_Level_03 :
	public CMonster
{
public:
	CMonster_Level_03();
	virtual ~CMonster_Level_03();

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void LateUpdate(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

private:
	virtual void Attack();
};

