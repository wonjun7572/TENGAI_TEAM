#pragma once

class CObj;

class CCollisionMgr
{

public:
	static bool	CheckSphere(CObj *_pTemp, CObj *_pSour);
	static void CollisionRect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void CollisionSphere(list<CObj*> _Dest, list<CObj*> _Sour);

public:

private:


public:
	CCollisionMgr();
	~CCollisionMgr();
};
