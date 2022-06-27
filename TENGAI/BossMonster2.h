#pragma once

#include "Obj.h"
#include "AbstractFactory.h"

class CBossMonster2 : public CObj
{
public:
	CBossMonster2();
	virtual ~CBossMonster2();

	void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void Set_Bullet_Monster(list<CObj*>* pBullet) { m_pBullet_BossMonster2 = pBullet; }

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
	int iReverse;
	int iReverse2;
	list<CObj*>*	m_pBullet_Player;
	list<CObj*>*	m_pBullet_BossMonster2;

private:	// 앵글, cos, sin 필요한 변수.
	float	fAngle;
	float	fCos;
	float	fSin;
};
