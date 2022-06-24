#pragma once
#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

	// ���Ŀ� ���� ����Ʈ ������.
	//void Set_Monster(list<CObj*>* pMonster) { m_pMonster = pMonster; }
	void Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	//void Set_Monster(CObj* pMonster) { m_pMonster = pMonster; }

	void Set_Monster(list<CObj*>* pMonster) { m_pMonster = pMonster; }

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void			Key_Input(void);
	list<CObj*>*	m_pBullet;
	
	list<CObj*>*    m_pMonster;
	
	//CObj*			m_pMonster;
	DWORD dwTimer;
};

