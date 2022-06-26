#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void Set_Bullet_Monster(list<CObj*>* pBullet) { m_pBullet_Monster = pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void SetHp(int i) { m_tStat.Hp -= i; }
	virtual void SetDead() { m_dead = true; }

private:
	bool	bShooting = false;

	void			Key_Input(void);
	list<CObj*>*	m_pBullet_Player;
	list<CObj*>*	m_pBullet_Monster;
};

