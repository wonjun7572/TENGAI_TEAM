#pragma once
#include "Item.h"
class CAddShieldItem :
	public CItem
{

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	virtual bool CollisionCheck(RECT r1, RECT r2);

public:
	CAddShieldItem();
	virtual ~CAddShieldItem();

private:
	float		m_fAngle;
	float		m_fDiagonal;
	bool		m_Arrive;


};