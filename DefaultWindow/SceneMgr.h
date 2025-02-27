#pragma once

#include "Define.h"

#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "FirstStage.h"
#include "VillageStage.h"
#include "PuzzleStage.h"
#include "BossStage.h"
#include "FinalStage.h"
#include "MyEdit.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID		Get_Scene() { return m_eCurScene; }

	void		Scene_Change(SCENEID eID);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	static		CSceneMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pScene;

	SCENEID				m_ePreScene;
	SCENEID				m_eCurScene;
};

