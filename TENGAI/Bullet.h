#pragma once
#include "Obj.h"

class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void SetHp(int i) { m_tStat.Hp -= i; }
	virtual void SetDead() { m_dead = true; }

public:
	void Set_Monster(list<CObj*>* _pMonster) {
		m_pMonster = _pMonster;
	}

	void Set_BossMonster(list<CObj*>* _pBossMonster) {
		m_pBossMonster = _pBossMonster;
	}

	void SetEffect()
	{
		m_bEffect = true;
		m_fSpeed = 0.f;
	}

private:
	list<CObj*>*	m_pMonster;
	list<CObj*>*	m_pBossMonster;
	bool			m_bEffect = false;
	float			m_fExplosion = 0.f;
};

