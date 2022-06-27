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
	//void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void set_bulletCOunt(int i) { 
				
		test = i;
			}


public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	BulletCountUp() { m_tStat.BulletCount++; }

	list<CObj*>*    m_pPlayer;
	list<CObj*>*	m_pBullet_Pet;




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

