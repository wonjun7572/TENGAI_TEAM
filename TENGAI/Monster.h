#pragma once
#include "Obj.h"
#include "AbstractFactory.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

	void Set_Player(list<CObj*>* pPlayer) { m_pPlayer = pPlayer; }
	void Set_Pet(list<CObj*>* pPet) { m_pPet = pPet; }
	void Set_Bullet_Player(list<CObj*>* pBullet) { m_pBullet_Player = pBullet; }
	void Set_Bullet_Pet(list<CObj*>* pBullet) { m_pBullet_Pet = pBullet; }
	void Set_Bullet_Monster(list<CObj*>* pBullet) { m_pBullet_Monster = pBullet; }
	void Set_ObjList(list<CObj*>* _ObjIDList) { m_pItem = _ObjIDList; }

public:
	virtual void Initialize(void)PURE;
	virtual int  Update(void)PURE;
	virtual void LateUpdate(void)PURE;
	virtual void Render(HDC hDC)PURE;
	virtual void Release(void)PURE;

protected:
	virtual void CreateItem();
	virtual void Attack()PURE;

protected:
	int iReverse;
	list<CObj*>*    m_pPet;
	list<CObj*>*    m_pPlayer;
	list<CObj*>*	m_pBullet_Player;
	list<CObj*>*	m_pBullet_Pet;
	list<CObj*>*	m_pBullet_Monster;
	list<CObj*>*	m_pItem;
};

