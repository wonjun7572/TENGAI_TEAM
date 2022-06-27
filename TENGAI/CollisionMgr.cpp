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
				//  플레이어랑 몬스터가 충돌했을 땐 몬스터 사라지고 플레이어 체력 1 감소
				if ((Dest->GetOBJID() == OBJ_PLAYER))
				{
					Dest->HpDown();
					Sour->KillObj();
				}
				else
				{
					if (Sour->GetStat().Hp == 0)
					{
						//Sour->SetSpeed(Dest->GetSpeed() * -1.f);
						break;
					}
					Dest->HpDown();
					Sour->HpDown();
				}
			}
			//Dest->SetDead(true);
			//Sour->SetDead(true);
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
				//  플레이어랑 몬스터가 충돌했을 땐 몬스터 사라지고 플레이어 체력 1 감소
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
					//if (Sour->GetStat().Hp == 0)
					//{
						//Sour->SetSpeed(Dest->GetSpeed() * -1.f);
					//	continue;
					//}
					Dest->HpDown();
					Sour->HpDown();
				}
				/*
				if (Dest->GetOBJID() == OBJ_PLAYER)
				{
				static_cast<CPlayer*>(Dest)->setHp(1);
				}
				if (Sour->GetOBJID() == OBJ_PLAYER)
				{
				static_cast<CPlayer*>(Sour)->setHp(1);
				}
				if (Dest->GetOBJID() == OBJ_MONSTER)
				{
				static_cast<CMonster_Level_01*>(Dest)->setHp(1);
				}
				if (Sour->GetOBJID() == OBJ_MONSTER)
				{
				static_cast<CMonster_Level_01*>(Sour)->setHp(1);
				}
				if(Dest->GetOBJID() != OBJ_PLAYER
				|| Sour->GetOBJID() != OBJ_PLAYER
				|| Dest->GetOBJID() != OBJ_MONSTER
				|| Sour->GetOBJID() != OBJ_MONSTER)
				{
				Dest->SetDead(true);
				Sour->SetDead(true);
				}
				*/
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
	// c^2 = x^2 + y^2

	// d <= r1 + r2 

	float fWidth = fabs(_pTemp->GetInfo().fX - _pSour->GetInfo().fX);
	float fHeight = fabs(_pTemp->GetInfo().fY - _pSour->GetInfo().fY);

	// 거리 = 빗변의 길이 구하는 법  // c^2 = x^2 + y^2
	float fDiagonal = sqrtf(fWidth*fWidth) + sqrtf(fHeight*fHeight);

	// 반지름 구하는 법 float 는 비트연산자가 안된다.
	//		r1 + r2 
	// 애초에 지금 
	// m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	// m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	// m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	// m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
	//  ex) fx 50 이 중점이면 left 0 , right 100 이렇게 되는 코딩이다.
	//		그래서 fcx* 0.5 가 반지름이 되는 것이다.

	float fRadius = static_cast<float>(_pTemp->GetInfo().fCX + _pSour->GetInfo().fCX)*0.5f;

	return fDiagonal <= fRadius;
}

bool CCollisionMgr::CheckSphereAndRect(CObj * _pSphere, CObj * _pRect)
{
	if ((_pSphere->GetInfo().fX < _pRect->GetRect().left) &&
		(fabs(_pSphere->GetInfo().fX - _pRect->GetRect().left) < fabs(_pSphere->GetInfo().fX + (_pSphere->GetInfo().fCX * 0.5f))))
	{
		return false;
	}
	else if ((_pSphere->GetInfo().fY < _pRect->GetRect().top) &&
		(fabs(_pSphere->GetInfo().fY - _pRect->GetRect().top) < fabs(_pSphere->GetInfo().fY + (_pSphere->GetInfo().fCY * 0.5f))))
	{
		return false;
	}
	else if ((_pSphere->GetInfo().fX > _pRect->GetRect().right) &&
		(fabs(_pSphere->GetInfo().fX - _pRect->GetRect().right) < fabs(_pSphere->GetInfo().fX + (_pSphere->GetInfo().fCX * 0.5f))))
	{
		return false;
	}
	else if ((_pSphere->GetInfo().fY > _pRect->GetRect().bottom) &&
		(fabs(_pSphere->GetInfo().fY - _pRect->GetRect().bottom) < fabs(_pSphere->GetInfo().fY + (_pSphere->GetInfo().fCY * 0.5f))))
	{
		return false;
	}

	return false;
}

void CCollisionMgr::Collision_Sphere_Rect(list<CObj*> _pSphere, list<CObj*> _pRect)
{
	for (auto &Sphere : _pSphere)
	{
		for (auto &Rect : _pRect)
		{
			if (CheckSphereAndRect(Sphere, Rect))
			{
				if (0 >= Sphere->GetStat().Hp)
					continue;
				else
				{
					Sphere->HpDown();
					Rect->HpDown();
				}
			}
		}
	}
}
