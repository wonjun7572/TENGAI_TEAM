#pragma once

class CObj;

class CCollisionMgr
{

public:
	static bool	CheckSphere(CObj *_pTemp, CObj *_pSour);
	static void CollisionRect(list<CObj*> _Dest, list<CObj*> _Sour);
	/*static void CollisionSphere(list<CObj*> _Dest, list<CObj*> _Sour);*/
	static bool CollisionSphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static void CCollisionMgr::CollisionWall(list<CObj*> _Dest);
	static void CollisionWall2(list<CObj*> _Dest);

public:
	CCollisionMgr();
	~CCollisionMgr();
};

