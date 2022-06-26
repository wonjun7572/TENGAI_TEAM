#include "pch.h"
#include "AddPetPowerUp.h"
#include "pet.h"

CAddPetPowerUp::CAddPetPowerUp()
{
}

CAddPetPowerUp::~CAddPetPowerUp()
{
}

void CAddPetPowerUp::Initialize(void)
{
	m_tInfo = { 700.f,500.f,45.f,45.f };
	m_fSpeed = 3.f;
}

int CAddPetPowerUp::Update(void)
{
	if (m_dead == true)
	{
		dynamic_cast<CPet*>(GetPet())->BulletCountUp();
		return OBJ_DEAD;
	}

	m_tInfo.fX -= m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CAddPetPowerUp::LateUpdate(void)
{
	if (CollisionCheck(GetPlayer()->GetRect(), m_tRect))
	{
		m_dead = OBJ_DEAD;
	}
}

void CAddPetPowerUp::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	WCHAR szBuff[32] = L"PET";
	TextOut(hDC, m_tRect.left + 6.f, m_tRect.top + 10.f, szBuff, lstrlen(szBuff));
}

void CAddPetPowerUp::Release(void)
{
}

bool CAddPetPowerUp::CollisionCheck(RECT r1, RECT r2)
{
	RECT rc = {};

	if (IntersectRect(&rc, &r1, &r2))
	{
		return true;
	}

	return false;
}