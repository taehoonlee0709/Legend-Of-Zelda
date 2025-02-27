#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Monster.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"
#include "HeartUIMgr.h"
#include "TerrainObjMgr.h"
#include "InventoryMgr.h"
#include "RSPMgr.h"
#include "CoinMgr.h"


CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
	//: m_pPlayer(nullptr)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/back.bmp", L"Back");

	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);

#ifdef _DEBUG

	/*if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}*/

#endif // _DEBUG


}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{

	CSceneMgr::Get_Instance()->Late_Update();

	CScrollMgr::Get_Instance()->Scroll_Lock();

}

void CMainGame::Render()
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);	// 윈도우 상단에 글씨를 출력해줌

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	if (SC_LOGO == CSceneMgr::Get_Instance()->Get_Scene())
		return;

	
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	
	CSceneMgr::Get_Instance()->Render(hMemDC);

	BitBlt(m_hDC,
		0, 0, WINCX, WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);	
}

void CMainGame::Release()
{	
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

	CSoundMgr::Get_Instance()->Destroy_Instance();
	CTileMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CHeartUIMgr::Get_Instance()->Destroy_Instance();
	CTerrainObjMgr::Get_Instance()->Destroy_Instance();
	CInventoryMgr::Get_Instance()->Destroy_Instance();
	CRSPMgr::Get_Instance()->Destroy_Instance();
	CCoinMgr::Get_Instance()->Destroy_Instance();


	ReleaseDC(g_hWnd, m_hDC);	
}

