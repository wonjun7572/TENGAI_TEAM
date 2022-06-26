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
	void			Set_ObjList(list<CObj*>& temp) 
	{
		*m_ObjList = temp;
		//memcpy(m_ObjList, &temp, sizeof(temp.size()));

		
		/*for (int i = 0; i < OBJ_END; ++i)
		{
			for (auto iter = temp.begin(); iter != temp.end();)
			{
				Safe_Delete<CObj*>(*iter);
				iter = temp.erase(iter);
			}
		}
*/

	}	
	const bool			GetStageClear() const { return m_bStageClear; }
	void				SetStageClear(bool _bStageClear) { m_bStageClear = _bStageClear; }

public:
	CScene();
	//CScene(list<CObj*> _temp);
	
	//CScene(list<CObj*>	&rhs)
	//{
	////	memcpy(m_ObjList, &rhs, sizeof(rhs.size()));
	//}

	CScene(const CScene &rhs)
	{
		

	}


	virtual ~CScene();




protected:
	list<CObj*>		m_ObjList[OBJ_END];
	DWORD			m_dwTimer;
	bool			m_bStageClear;

};

