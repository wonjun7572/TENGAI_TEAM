#include "pch.h"
#include "Scene.h"


CScene::CScene()
	:m_bStageClear(false), m_dwTimer(0), m_IScore(0), m_bStageEmptyCheck(false)
{
}

CScene::CScene(list<CObj*>* temp)
	: m_bStageClear(false), m_dwTimer(0), m_bStageEmptyCheck(false)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		m_ObjList[i].assign(temp[i].begin(), (temp[i].end()));
	}
}

CScene::~CScene()
{

}
