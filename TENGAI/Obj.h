#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

	void Set_Pos(float _fX, float _fY, DIR _dir = DIR_END)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_eDir = _dir;
	}

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	LateUpdate(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	bool		CollisionCheck(RECT rc1, RECT rc2);
	RECT		GetRect() { return m_tRect; }
	void		SetDead(bool _dead) { m_dead = _dead; }


public:


protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIR			m_eDir;

	float		m_fSpeed = 0.f;
	bool		m_dead;

protected:
	
	// 메인게임의 오브제인덱스중 하나를 가지기 위한 list의 포인터를 가져옴
	
};

