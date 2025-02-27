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
		m_tRect.left, // ���� ���� ��ġ x, y ��ǥ
		m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,		// ������ �̹��� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		(int)m_tInfo.fCX,	// ������ �̹����� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(128, 128, 128));
}

void CItemButtonUI::Release()
{
}
