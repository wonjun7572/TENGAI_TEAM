#pragma once
#include "Include.h"

class CObj;


class CScene
{


public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual void	LateUpdate(void)	PURE;
	virtual int	Render(HDC hDC)		PURE;
	virtual void	Release(void)		PURE;

public:
	list<CObj*>*	Get_ObjList() { return m_ObjList; }
	void			Set_ObjList(list<CObj*>& temp) {
		*m_ObjList = temp;
	}	
	const bool			GetStageClear() const { return m_bStageClear; }
	void				SetStageClear(bool _bStageClear) { m_bStageClear = _bStageClear; }

public:
	const int		Get_Score() { return m_IScore; }
	void			Set_Score(int _iScore) { m_IScore = _iScore; }
public:
	CScene();
	CScene(list<CObj*>* temp)
	{
		list<CObj*>*  new_ObjList = new list<CObj*>;

		memcpy(new_ObjList, &temp, sizeof(temp));

		*m_ObjList = *new_ObjList;
	}

	CScene(int i)
	{

		i = 0;
		/*list<CObj*>*  new_ObjList = new list<CObj*>;

		memcpy(new_ObjList, &temp, sizeof(temp));

		*m_ObjList = *new_ObjList;*/
	}

	/*CScene(list<CObj*> temp)
	{
		list<CObj*>*  new_ObjList = new list<CObj*>;

		memcpy(new_ObjList, &temp, sizeof(temp));
		
		*m_ObjList = *new_ObjList;

	}*/
	//CScene(CScene & rhs)
	//{
	//	


	//}
	virtual ~CScene();

protected:
	int				m_IScore;


protected:
	list<CObj*>		m_ObjList[OBJ_END];
	DWORD			m_dwTimer;
	bool			m_bStageClear;

};

