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
		m_tRect.left, // ���� ���� ��ġ x, y ��ǥ
		m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,		// ������ �̹��� dc
		0,			// ��Ʈ�� �̹��� ��� ���� ��ǥ
		m_iDrawID * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,	// ������ �̹����� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(128, 128, 128));	// �����ϰ��� �ϴ� ����

}

void CMyButton::Release()
{
}
