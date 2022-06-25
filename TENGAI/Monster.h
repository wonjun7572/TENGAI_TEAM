#pragma once
#include "Obj.h"
#include "AbstractFactory.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void Set_Bullet_Monster(list<CObj*>* pBullet) { m_pBullet_Monster = pBullet; }
	void Set_ObjList(list<CObj*>* _ObjIDList) { m_pItem = _ObjIDList; }
public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void CreateItem();
	void Attack();

private:
	int iReverse;
	list<CObj*>*	m_pBullet_Player;
	list<CObj*>*	m_pBullet_Monster;
	list<CObj*>*	m_pItem;


private:	//	패턴 중복 방지용 bool변수
	bool bPattern_A;
	bool bPattern_B;
	bool bPattern_C;
};

