#include "pch.h"
#include "Scene.h"


CScene::CScene()
	:m_bStageClear(false) , m_dwTimer(0), m_IScore (0), m_bStageEmptyCheck(false)
{
}

//CScene::CScene(list<CObj*> temp)
//{
//
//	list<CObj*> new_ObjList;
//
//
//	
//			
//
//	//
//	//for (int i = 0; i < OBJ_END; ++i)
//	//{
//	//	m_ObjList[i].assign(new_ObjList[i].begin(), (new_ObjList[i].end()));
//	//}
//	
//	
//}


CScene::CScene(list<CObj*>* temp)
:m_bStageClear(false) , m_dwTimer(0), m_bStageEmptyCheck(false)
{



		for (int i = 0; i < OBJ_END; ++i)
		{
			m_ObjList[i].assign(temp[i].begin(), (temp[i].end()));
		}


		
		//memcpy(new_ObjList, temp, sizeof(temp));



	/*	for (int i = 0; i < OBJ_END; ++i)
		{
			new_ObjList[i].assign(temp[i].begin(), (temp[i].end()));
		}*/
		//new_ObjList->assign(temp.begin(), (temp.end()));
		
		
		//new_ObjList->assign(temp->begin(), (temp->end()));
		
		/*for (int i = 0; i < OBJ_END; ++i)
		{
			m_ObjList[i].assign(&new_ObjList[i].begin(), &new_ObjList[i].end());
		}*/


		//m_ObjList->assign(new_ObjList->begin(), (new_ObjList->end()));

	/*	for (int i = 0; i < OBJ_END; ++i)
		{
			m_ObjList[i].assign(new_ObjList[i].begin(), (new_ObjList[i].end()));
		}*/



}





CScene::~CScene()
{
	
}
//if (0 == m_ObjList[OBJ_MONSTER].size() && 0 == m_ObjList[OBJ_BOSSMONSTER].size() && !m_bStageEmptyCheck)
//{
//	m_dwTimer = GetTickCount();
//	m_bStageEmptyCheck = true;
//}