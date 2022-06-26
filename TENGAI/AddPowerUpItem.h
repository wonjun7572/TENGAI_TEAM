#pragma once
#include "Item.h"
class CAddPowerUpItem :
	public CItem
{
public:
	CAddPowerUpItem();
	virtual ~CAddPowerUpItem();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual bool CollisionCheck(RECT r1, RECT r2);
};

