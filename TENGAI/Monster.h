#pragma once
#include "Obj.h"
#include "AbstractFactory.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	void Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void Set_ObjList(list<CObj*>* _ObjIDList) { m_pItem = _ObjIDList; }
public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void CreateItem();

private:
	int iReverse;
	list<CObj*>*	m_pBullet;
	list<CObj*>*	m_pItem;

//	(list<CObj*>*)*	m_objList;

};

