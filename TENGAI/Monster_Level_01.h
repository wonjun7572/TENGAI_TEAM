#pragma once
#include "Monster.h"
class CMonster_Level_01 :
	public CMonster
{
public:
	CMonster_Level_01();
	virtual ~CMonster_Level_01();

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void LateUpdate(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
	virtual void SetHp(int i) { m_tStat.Hp -= i; }
	virtual void SetDead() { m_dead = true; }

private:
	virtual void CreateItem();
	virtual void Attack();
};

