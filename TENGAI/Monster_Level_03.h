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
	void SetEffect()
	{
		m_bEffect = true;
		m_fSpeed = 0.f;
	}

private:
	virtual void Attack();

private:
	bool		m_bEffect = false;
	float		m_fExplosion = 0.f;
};

