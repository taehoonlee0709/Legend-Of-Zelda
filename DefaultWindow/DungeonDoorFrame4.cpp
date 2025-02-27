#include "stdafx.h"
#include "DungeonDoorFrame4.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CDungeonDoorFrame4::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/DungeonDoorFrame4.bmp", L"DungeonDoorFrame4");
	m_pFrameKey = L"DungeonDoorFrame4";
	m_tInfo.fCX = DUNGEON_DOOR_FRAME4_CX;
	m_tInfo.fCY = DUNGEON_DOOR_FRAME4_CY;

	m_eRender = RENDER_BACKGROUND_HIGH;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CDungeonDoorFrame4::Update()
{
	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CDungeonDoorFrame4::Late_Update()
{
}

void CDungeonDoorFrame4::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,		// ������ �̹��� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		(int)m_tInfo.fCX,	// ������ �̹����� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
}

void CDungeonDoorFrame4::Release()
{
}
