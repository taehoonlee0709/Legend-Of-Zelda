#include "stdafx.h"
#include "ItemButtonUI.h"
#include "BmpMgr.h"


void CItemButtonUI::Initialize()
{
	m_tInfo = { ITEM_BUTTON_UI_POSX,ITEM_BUTTON_UI_POSY,ITEM_BUTTON_UI_CX,ITEM_BUTTON_UI_CY };

	//m_fSpeed = 5.f;
	//m_fDistance = 100.f;
	//m_fAngle = 90.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Item_Button_UI.bmp", L"Item_Button_UI");



	m_pFrameKey = L"Item_Button_UI";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;

	m_eRender = RENDER_UI_LOW;
}

int CItemButtonUI::Update()
{
	__super::Update_Rect();

	return 0;
}

void CItemButtonUI::Late_Update()
{
}

void CItemButtonUI::Render(HDC hDC)
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
		RGB(128, 128, 128));
}

void CItemButtonUI::Release()
{
}
