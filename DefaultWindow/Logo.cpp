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

	m_hVideo = MCIWndCreate(g_hWnd,			// �θ��� ������ �ڵ��� ����
							nullptr,		// MCI �����츦 ����ϴ� �ν��Ͻ� �ڵ�
							WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, // �ڽ�â | ��� ��� | �÷��̹� �������� ����
							L"../Video/Opening.wmv");

	// MoveWindow : ������ ��� ũ�� ����
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
