#include "stdafx.h"
#include "HeartUI.h"
#include "BmpMgr.h"


void CHeartUI::Initialize()
{
	m_tInfo = { HEART_UI_POSX, HEART_UI_POSY, HEART_UI_CX, HEART_UI_CY };

	//m_fSpeed = 5.f;
	//m_fDistance = 100.f;
	//m_fAngle = 90.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Heart_UI.bmp", L"Heart_UI");



	m_pFrameKey = L"Heart_UI";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;

	m_eRender = RENDER_UI_LOW;

}

int CHeartUI::Update()
{
	__super::Update_Rect();

	return 0;
}

void CHeartUI::Late_Update()
{
}

void CHeartUI::Render(HDC hDC)
{


	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left, // 복사 받을 위치 x, y 좌표
		m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,		// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
		(int)m_tInfo.fCX,	// 복사할 이미지의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(167, 167, 227));
}

void CHeartUI::Release()
{
}

void CHeartUI::Move_Frame()
{
	++m_tFrame.iFrameStart;
	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		m_tFrame.iFrameStart = 4;
}
