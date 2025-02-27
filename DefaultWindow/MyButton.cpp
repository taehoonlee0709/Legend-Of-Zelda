#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"


CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 150.f;

	m_eRender = RENDER_UI_LOW;
}

int CMyButton::Update()
{
	__super::Update_Rect();

	return 0;
}

void CMyButton::Late_Update()
{
	POINT	Pt{};
	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	if (PtInRect(&m_tRect, Pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Start", m_pFrameKey))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSceneMgr::Get_Instance()->Scene_Change(SC_LINKHOME_STAGE);
			}

			else if (!lstrcmp(L"Edit", m_pFrameKey))
			{
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);
			}

			else if (!lstrcmp(L"Exit", m_pFrameKey))
				DestroyWindow(g_hWnd);

			return;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;


}

void CMyButton::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left, // 복사 받을 위치 x, y 좌표
		m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,		// 복사할 이미지 dc
		0,			// 비트맵 이미지 출력 시작 좌표
		m_iDrawID * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,	// 복사할 이미지의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(128, 128, 128));	// 제거하고자 하는 색상값

}

void CMyButton::Release()
{
}
