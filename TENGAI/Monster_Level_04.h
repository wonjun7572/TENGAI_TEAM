#pragma once
#include "Monster.h"
class CMonster_Level_04 :
	public CMonster
{
public:
	CMonster_Level_04();
	virtual ~CMonster_Level_04();

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void LateUpdate(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

private:
	virtual void CreateItem();
	virtual void Attack();

private:
	float fCos;
	float fSin;
	float fAtan;
	float fACos;
	float fASin;

};
