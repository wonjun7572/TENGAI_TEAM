#pragma once

class CObj;

class CCollisionMgr
{

public:
	static bool	CheckSphere(CObj *_pTemp, CObj *_pSour);
	static bool	CheckSphereAndRect(CObj *_pSphere, CObj *_pRect);
	static void Collision_Sphere_Rect(list<CObj*> _pSphere, list<CObj*> _pRect);
	static void CollisionRect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void CollisionSphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static void CCollisionMgr::CollisionWall(list<CObj*> _Dest);
	static void CollisionWall2(list<CObj*> _Dest);

public:

private:


public:
	CCollisionMgr();
	~CCollisionMgr();
};

