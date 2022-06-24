#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

	

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	LateUpdate(void)	PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	const RECT		GetRect() const  { return m_tRect; }
	const INFO		GetInfo() const { return m_tInfo; }
	const OBJID		GetOBJID() const { return m_eObjID;}
	void Set_Pos(float _fX, float _fY, DIR _dir = DIR_END)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
		m_eDir = _dir;
	}
	
	
	void			SetDead(bool _dead) { m_dead = _dead; }
	void			SetObjID(OBJID _eObjID) { m_eObjID = _eObjID; }

public:
	

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	STAT		m_tStat;
	RECT		m_tRect;
	DIR			m_eDir;
	OBJID		m_eObjID;

	float		m_fSpeed = 0.f;
	bool		m_dead;

protected:
	
	// 메인게임의 오브제인덱스중 하나를 가지기 위한 list의 포인터를 가져옴
	
};

