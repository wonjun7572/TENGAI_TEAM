#pragma once
#include "CollisionMgr.h"
#include "Obj.h"

class CItem :
	public CObj
{
public:
	virtual void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

	virtual void Initialize(void)	 PURE;
	virtual int  Update(void)	     PURE;
	virtual void LateUpdate(void)	 PURE;
	virtual void Render(HDC hDC)	 PURE;
	virtual void Release(void)		 PURE;

	CObj* GetPlayer() { return m_pPlayer; }

	virtual bool CollisionCheck(RECT r1, RECT r2) PURE;

	void SetCheck() { m_bCheck = true; }
	bool GetCheck() { return m_bCheck; }

public:
	CItem();
	virtual ~CItem();

private:
	bool	m_bCheck;
	CObj*	m_pPlayer;
};

