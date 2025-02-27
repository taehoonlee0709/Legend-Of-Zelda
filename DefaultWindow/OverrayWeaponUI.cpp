#include "stdafx.h"
#include "OverrayWeaponUI.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void COverrayWeaponUI::Initialize()
{
	//m_tInfo = { ITEM_BUTTON_UI_POSX,ITEM_BUTTON_UI_POSY,ITEM_BUTTON_UI_CX,ITEM_BUTTON_UI_CY };

	//m_fSpeed = 5.f;
	//m_fDistance = 100.f;
	//m_fAngle = 90.f;
	m_tInfo.fCX = OVERRAY_WEAPON_UI_CX;
	m_tInfo.fCY = OVERRAY_WEAPON_UI_CY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/SwordUI.bmp", L"SwordUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/StaffUI.bmp", L"StaffUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ShieldUI.bmp", L"ShieldUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BoomerangUI.bmp", L"BoomerangUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/rangUI.bmp", L"rangUI");



	m_pFrameKey = L"rangUI";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;

	m_eRender = RENDER_UI;
}

int COverrayWeaponUI::Update()
{
	__super::Update_Rect();

	return 0;
}

void COverrayWeaponUI::Late_Update()
{
}

void COverrayWeaponUI::Render(HDC hDC)
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
		RGB(192, 192, 255));
	/*int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);*/
}

void COverrayWeaponUI::Release()
{
}

void COverrayWeaponUI::ChangeWeapon(ITEMCODE _eItemcode)
{
	switch (_eItemcode)
	{
	case SWORD:
		m_pFrameKey = L"SwordUI";
		break;
	case WAND:
		m_pFrameKey = L"StaffUI";
		break;
	case SHIELD:
		m_pFrameKey = L"ShieldUI";
		break;
	case BOOMERANG:
		m_pFrameKey = L"BoomerangUI";
		break;
	default:
		break;
	}
}
