#pragma once

#include "Obj.h"
#include "AbstractFactory.h"

class CBossMonster : public CObj
{
public:
	CBossMonster();
	virtual ~CBossMonster();

	void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void Set_Bullet_Monster(list<CObj*>* pBullet) { m_pBullet_BossMonster = pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void SetHp(int i) { m_tStat.Hp -= i; }
	virtual void SetDead() { m_dead = true; }

private:
	void Attack();

private:
	int	iBoss_Hp;
	int iReverse;
	int iReverse2;
	list<CObj*>*	m_pBullet_Player;
	list<CObj*>*	m_pBullet_BossMonster;




private:	//	패턴 중복 방지용 bool변수
	bool bPattern_A;
	bool bPattern_B;
	bool bPattern_C;

private:	// 앵글, cos, sin 필요한 변수.
	float	fAngle;
	float	fCos;
	float	fSin;
};

