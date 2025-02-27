#include "stdafx.h"
#include "VillageDoorFrame3.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

void CVillageDoorFrame3::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/TownDoorFrame3.bmp", L"TownDoorFrame3");
	m_pFrameKey = L"TownDoorFrame3";
	m_tInfo.fCX = TOWN_DOOR_FRAME3_CX;
	m_tInfo.fCY = TOWN_DOOR_FRAME3_CY;

	m_eRender = RENDER_BACKGROUND_HIGH;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CVillageDoorFrame3::Update()
{
	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CVillageDoorFrame3::Late_Update()
{
}

void CVillageDoorFrame3::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // 복사 받을 위치 x, y 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,		// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
		(int)m_tInfo.fCX,	// 복사할 이미지의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거하고자 하는 색상값
}

void CVillageDoorFrame3::Release()
{
}
