#pragma once
#include "Monster.h"
class CMonster_Level_05 :
	public CMonster
{
public:
	CMonster_Level_05();
	virtual ~CMonster_Level_05();

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void LateUpdate(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

private:
	virtual void CreateItem();
	virtual void Attack();
	virtual void SetHp(int i) { m_tStat.Hp -= i; }
	virtual void SetDead() { m_dead = true; }

};

