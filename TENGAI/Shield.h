#pragma once
#include "Obj.h"
class CShield : public CObj
{

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


public:
	void		Set_ShieldCheck(bool _bTrue) { m_bShieldCheck = _bTrue; }
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void		SetEffect()
	{
		m_bEffect = true;
		m_fSpeed = 0.f;
	}

public:
	CShield();
	virtual ~CShield();

private:
	bool		m_bShieldCheck = false;
	float		m_fAngle;
	float		m_fDiagonal;
	bool		m_bEffect = false;
	float		m_fExplosion = 0.f;

private:

	CObj*    m_pPlayer;

};

