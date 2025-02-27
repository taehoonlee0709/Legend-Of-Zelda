#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"
#include "InventoryMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "Player.h"

void CItem::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/SwordInven.bmp", L"SwordInven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/StaffInven.bmp", L"StaffInven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/ShieldInven.bmp", L"ShieldInven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/BoomerangInven.bmp", L"BoomerangInven");
	m_pFrameKey = L"SwordInven";
	m_eItemCode = SWORD;
	m_iHp = 0;
	m_eRender = RENDER_GAMEOBJECT;

	m_tInfo.fCX = INVENTORY_SLOT_ITEM_CX;
	m_tInfo.fCY = INVENTORY_SLOT_ITEM_CY;

}

void CItem::Late_Update()
{
	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size() && m_bInvincibility == false)
		{
			RECT rc{};
			if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &this->Get_Rect()))
			{
				CInventoryMgr::Get_Instance()->Add_Item(this);
				//m_bDead = true;
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Item(this);
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Motion_Change();
				m_bInvincibility = true;
			}
		}
	}
}

void CItem::Render(HDC hDC)
{
	if (true == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		HDC	hItemBGDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		int iRowIndex = Get_Hp() % 4;
		int iLineIndex = Get_Hp() / 4;
		GdiTransparentBlt(hDC,
			INVENTORY_FIRST_SLOT_POSX + iRowIndex * INVENTORY_NEXT_ROW, // ���� ���� ��ġ x, y ��ǥ
			INVENTORY_FIRST_SLOT_POSY + iLineIndex * INVENTORY_NEXT_LINE,
			INVENTORY_SLOT_ITEM_CX,	// ���� ���� ����, ���� ����
			INVENTORY_SLOT_ITEM_CY,
			hItemBGDC,		// ������ �̹��� dc
			0,
			0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
			INVENTORY_SLOT_ITEM_CX,	// ������ �̹����� ����, ���� ������
			INVENTORY_SLOT_ITEM_CY,
			RGB(192, 192, 255));	// �����ϰ��� �ϴ� ����
	}
	else
	{
		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
			m_tRect.top + iScrollY,
			INVENTORY_SLOT_ITEM_CX,	// ���� ���� ����, ���� ����
			INVENTORY_SLOT_ITEM_CY,
			hMemDC,		// ������ �̹��� dc
			INVENTORY_SLOT_ITEM_CX * m_tFrame.iFrameStart,
			INVENTORY_SLOT_ITEM_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
			INVENTORY_SLOT_ITEM_CX,	// ������ �̹����� ����, ���� ������
			INVENTORY_SLOT_ITEM_CY,
			RGB(192, 192, 255));	// �����ϰ��� �ϴ� ����
	}
}
