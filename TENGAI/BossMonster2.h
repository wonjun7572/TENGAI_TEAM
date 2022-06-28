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
	list<CObj*>*	m_pBullet_BossMonster2;

private:	// 앵글, cos, sin 필요한 변수. 보스몬스터 패턴 앵글값 정의.
	bool	bAngle;
	float	fAngle;
	float	fAngle2;
	float	fCos;
	float	fSin;

	float		fCount = 0;

protected:
	list<CObj*>*    m_pPet;
	list<CObj*>*    m_pPlayer;

private:
	void SetEffect()
	{
		m_bEffect = true;
		m_fSpeed = 0.f;
	}

private:
	bool		m_bEffect = false;
	float		m_fExplosion = 0.f;
};
