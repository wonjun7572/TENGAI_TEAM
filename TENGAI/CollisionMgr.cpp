#include "pch.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Bullet.h"
#include "Monster_Level_01.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto &Dest : _Dest)
	{
		for (auto &Sour : _Sour)
		{
			if (0 == Dest->GetStat().Hp)
				continue;
			if (0 == Sour->GetStat().Hp)
				continue;

			if (IntersectRect(&RECT(), &Dest->GetRect(), &Sour->GetRect()))
			{
				if ((Dest->GetOBJID() == OBJ_PLAYER))
				{
					Dest->HpDown();
					Sour->KillObj();
				}
				else
				{
					if (Sour->GetStat().Hp == 0)
						break;
			
					Dest->HpDown();
					Sour->HpDown();
				}
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto &Dest : _Dest)
	{
		for (auto &Sour : _Sour)
		{
			if (0 == Dest->GetStat().Hp)
				continue;
			
			if (0 == Sour->GetStat().Hp)
				continue;

			if (CheckSphere(Dest, Sour))
			{
				if ((Dest->GetOBJID() == OBJ_PLAYER))
				{
					Dest->HpDown();
					if ((Sour->GetOBJID() == OBJ_BULLET_MONSTER))
						Sour->HpDown();
					else
						Sour->KillObj();
				}
				else
				{
					Dest->HpDown();
					Sour->HpDown();
				}		
			}
		}
	}
}

void CCollisionMgr::CollisionWall(list<CObj*> _Dest)
{
	for (auto& Dest : _Dest)
	{
		if (!IntersectRect(&RECT(), &Dest->GetRect(), &g_WindowRect_MonsterHouse))
		{
			Dest->HpDown();
		}
	}
}

void CCollisionMgr::CollisionWall2(list<CObj*> _Dest)
{
	for (auto& Dest : _Dest)
	{
		if (!IntersectRect(&RECT(), &Dest->GetRect(), &g_WindowRect))
		{
			Dest->HpDown();
		}
	}
}

bool CCollisionMgr::CheckSphere(CObj *_pTemp, CObj *_pSour)
{
	float fWidth = fabs(_pTemp->GetInfo().fX - _pSour->GetInfo().fX);
	float fHeight = fabs(_pTemp->GetInfo().fY - _pSour->GetInfo().fY);
	float fDiagonal = sqrtf(fWidth*fWidth) + sqrtf(fHeight*fHeight);
	float fRadius = static_cast<float>(_pTemp->GetInfo().fCX + _pSour->GetInfo().fCX)*0.5f;
	return fDiagonal <= fRadius;
}