#pragma once
#include "Obj.h"
class CPet :
	public CObj
{
public:
	CPet();
	virtual ~CPet();
	void Set_Bullet_Pet(list<CObj*>* pBullet) { m_pBullet_Pet = pBullet; }
	void Set_Player(list<CObj*>* pPlayer) { m_pPlayer = pPlayer; }
	//////////////////////////////////////////////////////변경////////////////////////////////////////////////////////
	void Set_Monster(list<CObj*>* pMonster) { m_pMonster = pMonster; }
	void Set_BossMonster(list<CObj*>* pBossMonster) { m_pBossMonster = pBossMonster; }
	//////////////////////////////////////////////////////변경////////////////////////////////////////////////////////

	//void set_bulletCOunt(int i) { 
				
	//	test = i;
	//		}


public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	BulletCountUp() { m_tStat.BulletCount++; }

	list<CObj*>*    m_pPlayer;
	list<CObj*>*	m_pBullet_Pet;

	//////////////////////////////////////////////////////변경////////////////////////////////////////////////////////
	list<CObj*>*	m_pMonster;
	list<CObj*>*	m_pBossMonster;
	//////////////////////////////////////////////////////변경////////////////////////////////////////////////////////

private:
	int num = 0;
	float X;
	float Y;
	float fOldTimeX;
	float fOldTimeY;
	float fStop = 1.f;

	float fCos;
	float fSin;
	float fAtan;
	float fACos;
	float fASin;

	float m_int = 0;

	float test = 0;
};

