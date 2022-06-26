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
	virtual void	SetHp(int i)		PURE;
	virtual void	SetDead()			PURE;

public:
	const RECT		GetRect() const  { return m_tRect; }
	const INFO		GetInfo() const { return m_tInfo; }
	const OBJID		GetOBJID() const { return m_eObjID;}
	void Set_Pos(float _fX, float _fY, DIR _dir = DIR_END, float _fCos = 0, float _fSin = 0)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;

		m_fCos = _fCos;
		m_fSin = _fSin;

		m_eDir = _dir;
	}
	void			SetObjID(OBJID _eObjID) { m_eObjID = _eObjID; }
protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	STAT		m_tStat;
	RECT		m_tRect;
	DIR			m_eDir;
	OBJID		m_eObjID;
	DWORD		m_dwTimer;
	DWORD		m_dwTimer2;

	float		m_fSpeed = 0.f;
	bool		m_dead;

protected:	// 삼각함수값
	float	m_fCos;
	float	m_fSin;
	float	m_fAtan;
	// 메인게임의 오브제인덱스중 하나를 가지기 위한 list의 포인터를 가져옴
	
};

