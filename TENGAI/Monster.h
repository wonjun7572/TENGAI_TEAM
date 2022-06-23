#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	void Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int iReverse;
	list<CObj*>*	m_pBullet;
};

