#include "stdafx.h"
#include "InventoryMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ItemButtonUI.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "OverrayWeaponUI.h"

CInventoryMgr* CInventoryMgr::m_pInstance = nullptr;

CInventoryMgr::CInventoryMgr() :m_bIsOpenInventory(false), m_ItemSlotQ(nullptr), m_ItemSlotW(nullptr), m_iCursor(0)
{
}

CInventoryMgr::~CInventoryMgr()
{
	Release();
}

void CInventoryMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/BG_Inven.bmp", L"BG_Inven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/Inventory.bmp", L"Inventory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Item_Button_UI.bmp", L"Item_Button_UI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/Item_Title.bmp", L"Item_Title");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/Item_BackGround.bmp", L"Item_BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/InventoryCusor.bmp", L"InventoryCusor");
	m_bIsOpenInventory = false;


	//m_vecItem.push_back(CAbstractFactory<CItem>::Create_Obj());
	//m_vecItem.back()->Set_Hp(m_vecItem.size()- 1);
	//static_cast<CItem*>(m_vecItem.back())->Set_ItemCode(SWORD);
	//m_vecItem.back()->Set_FrameKey(L"SwordInven");
	//m_vecItem.push_back(CAbstractFactory<CItem>::Create_Obj());
	//m_vecItem.back()->Set_Hp(m_vecItem.size() - 1);
	//static_cast<CItem*>(m_vecItem.back())->Set_ItemCode(STAFF);
	//m_vecItem.back()->Set_FrameKey(L"StaffInven");

	/*m_ItemSlotQ = CAbstractFactory<CItem>::Create_Obj();
	m_ItemSlotQ->Set_Hp(0);
	static_cast<CItem*>(m_ItemSlotQ)->Set_ItemCode(SWORD);
	m_ItemSlotW = CAbstractFactory<CItem>::Create_Obj();
	m_ItemSlotW->Set_Hp(1);
	static_cast<CItem*>(m_ItemSlotW)->Set_ItemCode(STAFF);*/
}

int CInventoryMgr::Update()
{



	Key_Input();

	return 0;
}

void CInventoryMgr::Late_Update()
{
	if (false == m_bIsOpenInventory)
		return;
}

void CInventoryMgr::Render(HDC hDC)
{
	if (false == m_bIsOpenInventory)
		return;

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BG_Inven");
	HDC	hInventoryDC = CBmpMgr::Get_Instance()->Find_Image(L"Inventory");
	HDC	hItemButtonUIDC = CBmpMgr::Get_Instance()->Find_Image(L"Item_Button_UI");
	HDC	hItemTitleDC = CBmpMgr::Get_Instance()->Find_Image(L"Item_Title");
	HDC	hItemBGDC = CBmpMgr::Get_Instance()->Find_Image(L"Item_BackGround");
	HDC	hCursorDC = CBmpMgr::Get_Instance()->Find_Image(L"InventoryCusor");
	//��׶��� �κ� ���
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	//CObjMgr::Get_Instance()->Render(hDC);

	//int iStartPoint = (GetTickCount() % 1000) / 100;

	//�� �κ��丮 ���
	GdiTransparentBlt(hDC,
		int((WINCX - INVENTORY_CX) * 0.5f), // ���� ���� ��ġ x, y ��ǥ
		int((WINCY - INVENTORY_CY) * 0.5f),
		INVENTORY_CX,	// ���� ���� ����, ���� ����
		INVENTORY_CY,
		hInventoryDC,		// ������ �̹��� dc
		0,
		0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		INVENTORY_CX,	// ������ �̹����� ����, ���� ������
		INVENTORY_CY,
		RGB(192, 192, 255));	// �����ϰ��� �ϴ� ����

	//������ ��ư ������ ���
	GdiTransparentBlt(hDC,
		int(ITEM_BUTTON_UI_POSX - ITEM_BUTTON_UI_CX * 0.5f), // ���� ���� ��ġ x, y ��ǥ
		int(ITEM_BUTTON_UI_POSY - ITEM_BUTTON_UI_CY * 0.5f),
		(int)ITEM_BUTTON_UI_CX,	// ���� ���� ����, ���� ����
		(int)ITEM_BUTTON_UI_CY,
		hItemButtonUIDC,		// ������ �̹��� dc
		0,
		0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		(int)ITEM_BUTTON_UI_CX,	// ������ �̹����� ����, ���� ������
		(int)ITEM_BUTTON_UI_CY,
		RGB(128, 128, 128));	// �����ϰ��� �ϴ� ����


	//������ Ÿ��Ʋ ���
	GdiTransparentBlt(hDC,
		int(ITEM_TITLE_POSX - ITEM_TITLE_CX * 0.5f), // ���� ���� ��ġ x, y ��ǥ
		int(ITEM_TITLE_POSY - ITEM_TITLE_CY * 0.5f),
		(int)ITEM_TITLE_CX,	// ���� ���� ����, ���� ����
		(int)ITEM_TITLE_CY,
		hItemTitleDC,		// ������ �̹��� dc
		0,
		0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		(int)ITEM_TITLE_CX,	// ������ �̹����� ����, ���� ������
		(int)ITEM_TITLE_CY,
		RGB(192, 192, 255));	// �����ϰ��� �ϴ� ����
	//�������̿��������� ���
	if (2 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_OVERRAY_UI).size())
	{
		list<CObj*> OverrayUIList = CObjMgr::Get_Instance()->Get_ObjList(OBJ_OVERRAY_UI);
		auto iter = OverrayUIList.begin();
		if (nullptr != m_ItemSlotQ)
			static_cast<COverrayWeaponUI*>(*iter)->ChangeWeapon(static_cast<CItem*>(m_ItemSlotQ)->Get_ItemCode());
		++iter;
		if (nullptr != m_ItemSlotW)
			static_cast<COverrayWeaponUI*>(*iter)->ChangeWeapon(static_cast<CItem*>(m_ItemSlotW)->Get_ItemCode());
		for (auto iter = OverrayUIList.begin();
			iter != OverrayUIList.end();
			++iter)
		{

			(*iter)->Render(hDC);
		}
	}
	if (m_ItemSlotQ != nullptr)
	{
		int iRowIndex = m_ItemSlotQ->Get_Hp() % 4;
		int iLineIndex = m_ItemSlotQ->Get_Hp() / 4;
		GdiTransparentBlt(hDC,
			INVENTORY_FIRST_SLOT_POSX + iRowIndex * INVENTORY_NEXT_ROW, // ���� ���� ��ġ x, y ��ǥ
			INVENTORY_FIRST_SLOT_POSY + iLineIndex * INVENTORY_NEXT_LINE, //
			INVENTORY_SLOT_ITEM_CX,	// ���� ���� ����, ���� ����
			INVENTORY_SLOT_ITEM_CY,
			hItemBGDC,		// ������ �̹��� dc
			0,
			0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
			INVENTORY_SLOT_ITEM_CX,	// ������ �̹����� ����, ���� ������
			INVENTORY_SLOT_ITEM_CY,
			RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
	}
	if (m_ItemSlotW != nullptr)
	{

		int iRowIndex = m_ItemSlotW->Get_Hp() % 4;
		int iLineIndex = m_ItemSlotW->Get_Hp() / 4;
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
			RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
	}

	//������ ���
	for (auto iter = m_vecItem.begin();
		iter != m_vecItem.end();
		++iter)
	{
		(*iter)->Render(hDC);
	}
	//Ŀ�� ���

	int iRowIndex = m_iCursor % 4;
	int iLineIndex = m_iCursor / 4;
	int iStart = int((GetTickCount() % 1000) / 500);
	GdiTransparentBlt(hDC,
		int(INVENTORY_FIRST_SLOT_POSX + INVENTORY_SLOT_ITEM_CX * 0.5f - INVENTORY_CURSOR_CX * 0.5f) + iRowIndex * INVENTORY_NEXT_ROW, // ���� ���� ��ġ x, y ��ǥ
		int(INVENTORY_FIRST_SLOT_POSY + INVENTORY_SLOT_ITEM_CY * 0.5f - INVENTORY_CURSOR_CY * 0.5f) + iLineIndex * INVENTORY_NEXT_LINE,
		INVENTORY_CURSOR_CX,	// ���� ���� ����, ���� ����
		INVENTORY_CURSOR_CY,
		hCursorDC,		// ������ �̹��� dc
		iStart * INVENTORY_CURSOR_CX,
		0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		INVENTORY_CURSOR_CX,	// ������ �̹����� ����, ���� ������
		INVENTORY_CURSOR_CY,
		RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����

}

void CInventoryMgr::Release()
{

	for_each(m_vecItem.begin(), m_vecItem.end(), CDeleteObj());
	m_vecItem.clear();

}




void CInventoryMgr::Select_Item(ITEMSLOT _eID)
{
	if (m_vecItem.size() <= (size_t)m_iCursor)
		return;

	if (ITEMSLOT_Q == _eID)
	{
		m_ItemSlotQ = m_vecItem[m_iCursor];
	}
	else if (ITEMSLOT_W == _eID)
	{
		m_ItemSlotW = m_vecItem[m_iCursor];
	}
}

void CInventoryMgr::Add_Item(CObj* _pItem)
{
	CObj* pObj = new CItem;
	pObj->Initialize();
	pObj->Set_Hp(m_vecItem.size());
	ITEMCODE eItemCode = static_cast<CItem*>(_pItem)->Get_ItemCode();
	static_cast<CItem*>(pObj)->Set_ItemCode(eItemCode);

	switch (eItemCode)
	{
	case SWORD:
		pObj->Set_FrameKey(L"SwordInven");
		break;
	case WAND:
		pObj->Set_FrameKey(L"StaffInven");
		break;
	case SHIELD:
		pObj->Set_FrameKey(L"ShieldInven");
		break;
	case BOOMERANG:
		pObj->Set_FrameKey(L"BoomerangInven");
		break;

	case ITEMCODE_END:
		break;
	default:
		break;
	}
	m_vecItem.push_back(pObj);
}

void CInventoryMgr::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		m_bIsOpenInventory = !m_bIsOpenInventory;
		m_iCursor = 0;
	}

	if (true == m_bIsOpenInventory)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		{
			Select_Item(ITEMSLOT_Q);
		}
		if (CKeyMgr::Get_Instance()->Key_Down('W'))
		{
			Select_Item(ITEMSLOT_W);
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_UP))
		{
			if (4 <= m_iCursor)
				m_iCursor -= 4;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_DOWN))
		{
			if (7 >= m_iCursor)
				m_iCursor += 4;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
		{
			if (1 <= m_iCursor)
				--m_iCursor;
		}
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT))
		{
			if (10 >= m_iCursor)
				++m_iCursor;
		}
	}
}
