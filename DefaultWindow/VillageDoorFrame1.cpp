#include "stdafx.h"
#include "VillageDoorFrame1.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CVillageDoorFrame1::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/TownDoorFrame1.bmp", L"TownDoorFrame1");
	m_pFrameKey = L"TownDoorFrame1";
	m_tInfo.fCX = TOWN_DOOR_FRAME1_CX;
	m_tInfo.fCY = TOWN_DOOR_FRAME1_CY;

	m_eRender = RENDER_BACKGROUND_HIGH;


	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CVillageDoorFrame1::Update()
{
	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CVillageDoorFrame1::Late_Update()
{
}

void CVillageDoorFrame1::Render(HDC hDC)
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

void CVillageDoorFrame1::Release()
{
}
