#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_eCurScene(SC_LOGO), m_ePreScene(SC_END), m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_LINKHOME_STAGE:
			m_pScene = new CStage;
			break;
		case SC_FIRST_STAGE:
			m_pScene = new CFirstStage;
			break;
		case SC_VILLAGE_STAGE:
			m_pScene = new CVillageStage;
			break;
		case SC_PUZZLE_STAGE:
			m_pScene = new CPuzzleStage;
			break;
		case SC_BOSS_STAGE:
			m_pScene = new CBossStage;
			break;

		case SC_FINAL_STAGE:
			m_pScene = new CFinalStage;
			break;
		}
		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
