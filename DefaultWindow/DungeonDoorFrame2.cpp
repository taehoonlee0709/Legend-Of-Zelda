#include "stdafx.h"
#include "DungeonDoorFrame2.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CDungeonDoorFrame2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/DungeonDoorFrame2.bmp", L"DungeonDoorFrame2");
	m_pFrameKey = L"DungeonDoorFrame2";
	m_tInfo.fCX = DUNGEON_DOOR_FRAME2_CX;
	m_tInfo.fCY = DUNGEON_DOOR_FRAME2_CY;

	m_eRender = RENDER_BACKGROUND_HIGH;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CDungeonDoorFrame2::Update()
{
	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CDungeonDoorFrame2::Late_Update()
{
}

void CDungeonDoorFrame2::Render(HDC hDC)
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

void CDungeonDoorFrame2::Release()
{
}
