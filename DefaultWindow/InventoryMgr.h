#pragma once
#include "Define.h"
#include "Obj.h"

#define INVENTORY_CX 624
#define INVENTORY_CY 399


#define ITEM_TITLE_POSX	168
#define ITEM_TITLE_POSY 50

#define ITEM_TITLE_CX 336
#define ITEM_TITLE_CY 66

#define INVENTORY_MAX_ROW 4
#define INVENTORY_MAX_LINE 3

#define INVENTORY_FIRST_SLOT_POSX  200
#define INVENTORY_FIRST_SLOT_POSY  157
#define INVENTORY_SLOT_ITEM_CX  78
#define INVENTORY_SLOT_ITEM_CY  57
#define INVENTORY_SLOT_INTERVAL_CX  30
#define INVENTORY_SLOT_INTERVAL_CY  15

#define INVENTORY_NEXT_ROW	(INVENTORY_SLOT_ITEM_CX+INVENTORY_SLOT_INTERVAL_CX)
#define INVENTORY_NEXT_LINE (INVENTORY_SLOT_ITEM_CY+INVENTORY_SLOT_INTERVAL_CY)

#define INVENTORY_CURSOR_CX  84
#define INVENTORY_CURSOR_CY  72

enum ITEMSLOT { ITEMSLOT_Q, ITEMSLOT_W, ITEMSLOT_END };

class CInventoryMgr
{
private:
	CInventoryMgr();
	~CInventoryMgr();

public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	bool		Get_IsOpenInventory() { return m_bIsOpenInventory; }
	CObj* Get_ItemSlotQ() { return m_ItemSlotQ; }
	CObj* Get_ItemSlotW() { return m_ItemSlotW; }
	void		Select_Item(ITEMSLOT _eID);
	void		Add_Item(CObj* _pItem);//¾ÆÀÌÅÛ È¹µæ½Ã º¤ÅÍ¿¡ Çª½¬¹éÇÏ´Â ÇÔ¼ö.

	void		Key_Input();

private:
	vector<CObj*>  m_vecItem;
	int	m_iCursor;
	CObj* m_ItemSlotQ;
	CObj* m_ItemSlotW;
	bool m_bIsOpenInventory;


public:
	static CInventoryMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CInventoryMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CInventoryMgr* m_pInstance;
};

