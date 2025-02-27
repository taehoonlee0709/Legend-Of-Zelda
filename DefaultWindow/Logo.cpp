#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");

	m_hVideo = MCIWndCreate(g_hWnd,			// 부모의 윈도우 핸들을 전달
							nullptr,		// MCI 윈도우를 사용하는 인스턴스 핸들
							WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // 자식창 | 즉시 출력 | 플레이바 생성하지 않음
							L"../Video/Opening.wmv");

	// MoveWindow : 동영상 재생 크기 설정
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

int CLogo::Update()
{
	return 0;
}

void CLogo::Late_Update()
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo)
		|| CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}
	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}*/
}

void CLogo::Render(HDC hDC)
{

	/*HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt(hDC,
		0, 0, WINCX, WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);*/
}

void CLogo::Release()
{
	MCIWndClose(m_hVideo);
}
