#include "pch.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"

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
			Dest->SetDead(true);
			Sour->SetDead(true);
		}
	}

}




void CCollisionMgr::CollisionSphere(list<CObj*> _Dest, list<CObj*> _Sour)
{


	for (auto &Dest : _Dest)
	{
		for (auto &Sour : _Sour)
		{
			if (CheckSphere(Dest, Sour))
			{
				if (Dest->GetOBJID() == OBJ_PLAYER || Sour->GetOBJID() == OBJ_PLAYER)
				{
					static_cast<CPlayer*>(Dest)->setHp(1);
				}
				else
				{
					Dest->SetDead(true);
				}
				Sour->SetDead(true);
			}
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
