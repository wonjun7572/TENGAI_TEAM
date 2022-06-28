#pragma once
#include "Obj.h"
class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize(void) override;
	virtual int	 Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	bool	GetType() { return m_bType; }
	void	SetTrue() { m_bType = true; }
	void	SetFalse() { m_bType = false; }

private:
	bool	m_bType;
};

