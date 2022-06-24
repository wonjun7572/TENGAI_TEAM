#pragma once
#include "Obj.h"

class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


public:
	void getMonsterList(list<CObj*>* _pMonster) {
		m_pMonster = _pMonster;
	}

private:
	list<CObj*>*	m_pMonster;

};

