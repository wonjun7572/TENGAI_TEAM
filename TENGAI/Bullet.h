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

	void Set_Player_Info (INFO _pInfo) {
		m_pPlayerInfo = _pInfo;
	}

	void SetEffect()
	{
		m_bEffect = true;
		m_fSpeed = 0.f;
	}
	/*
private:
	float	m_fRotAngle;
	float	m_fRotSpeed;
	float	m_fDiagonal;
	float	m_fAngle;

	bool	m_bStart;
	*/

private:
	//POINT			m_tCenter;
	//POINT			m_tPosin;
	INFO			m_pPlayerInfo;
	list<CObj*>*	m_pMonster;
	list<CObj*>*	m_pBossMonster;
	bool			m_bEffect = false;
	float			m_fExplosion = 0.f;
	float			m_fAngle = 0.f;
	float			m_fDiagonal = 0.f;
};

