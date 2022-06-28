#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	void Set_Bullet_Shield(list<CObj*>* pBullet) { m_pBullet_Shield = pBullet; }

	void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void Set_Bullet_Monster(list<CObj*>* pBullet) { m_pBullet_Monster = pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	HpUP() { m_tStat.Hp++; }
	void	BulletCountUp() { m_tStat.BulletCount++; }
	void	UltimateCountUp() { m_tStat.UltimateCount++; }

	void	Set_ShieldCheck(bool _bShieldCheck) { m_bShieldCheck = _bShieldCheck; }
	void Set_Shield(list<CObj*>* _pBullet_Shield) { m_pBullet_Shield = _pBullet_Shield; }

private:
	float			m_ShieldAngle = 0.f;
	bool			m_bShooting = false;
	bool			m_bShieldCheck = false;
	bool			m_bShiledArrive = false;

	void			Key_Input(void);

	list<CObj*>*	m_pBullet_Player;
	list<CObj*>*	m_pBullet_Shield;
	list<CObj*>*	m_pBullet_Monster;
	list<CObj*>*	m_pShield;
};

