#pragma once
#include "Item.h"
class CAddHpItem :
	public CItem
{
public:
	CAddHpItem();
	virtual ~CAddHpItem();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void SetHp(int i) { m_tStat.Hp -= i; }
	virtual void SetDead() { m_dead = true; }

	virtual bool CollisionCheck(RECT r1, RECT r2);
};

