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
	void Set_Player(list<CObj*>* pPlayer) { m_pPlayer = pPlayer; }
	void Set_Pet(list<CObj*>* pPet) { m_pPet = pPet; }

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
	list<CObj*>*	m_pBullet_BossMonster;

private:	// 앵글, cos, sin 필요한 변수.
	float	fAngle;
	float	fCos;
	float	fSin;

protected:
	list<CObj*>*    m_pPet;
	list<CObj*>*    m_pPlayer;
};

