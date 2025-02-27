#include "stdafx.h"
#include "PressureButton.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "TerrainObjMgr.h"
#include "PuzzleMgr.h"
#include "BossPuzzleMgr.h"

void CPressureButton::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/PressureButton.bmp", L"PressureButton");
	m_pFrameKey = L"PressureButton";
	m_tInfo.fCX = PRESSURE_BUTTON_CX;
	m_tInfo.fCY = PRESSURE_BUTTON_CY;
	//m_fSpeed = 4.f;
	m_eRender = RENDER_BACKGROUND;

	//m_dwDelayTime = GetTickCount() + (DWORD)STAFF_BULLET_DELAY;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 1000;
}

int CPressureButton::Update()
{

	m_tFrame.iFrameStart = 0;
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPressureButton::Late_Update()
{
	//�浹���϶� ���� ���·� �ƴϸ� �ö���ִ� ���·�����.
	if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
	{
		RECT rc{};
		if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &this->Get_Rect()))
		{
			m_tFrame.iFrameStart = 1;
			
		}

	}
	list<CObj*> templist = CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_MOVABLE_STONE);
	for (auto iter = templist.begin();
		iter != templist.end();
		++iter)
	{
		RECT rc{};
		if (IntersectRect(&rc, &(*iter)->Get_Rect(), &this->Get_Rect()))
		{
			m_tFrame.iFrameStart = 1;
			break;
		}
	}
	if (m_tFrame.iFrameStart == 1)
	{
		CPuzzleMgr::Get_Instance()->Set_TriggerCount();
		CBossPuzzleMgr::Get_Instance()->Set_TriggerCount();

	}
}

void CPressureButton::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//BitBlt(hDC,
	//	m_tRect.left + iScrollX,
	//	m_tRect.top + iScrollY,
	//	(int)PRESSURE_BUTTON_CX,
	//	(int)PRESSURE_BUTTON_CY,
	//	hMemDC,
	//	(int)m_tInfo.fCX * m_tFrame.iFrameStart,		//0,
	//	(int)m_tInfo.fCY * m_tFrame.iMotion,		//0,
	//	SRCCOPY);

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
		RGB(48, 80, 64));	// �����ϰ��� �ϴ� ����

}

void CPressureButton::Release()
{
}
