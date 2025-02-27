#include "stdafx.h"
#include "Stage.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include "Snake.h"
#include "TerrainObjMgr.h"
#include "CollisionMgr.h"
#include "Door.h"
#include "SceneMgr.h"
#include "InventoryMgr.h"
#include "HeartUIMgr.h"
#include "HeartUI.h"
#include "ItemButtonUI.h"
#include "OverrayWeaponUI.h"
#include "Grandpa.h"
#include "TextBoxMgr.h"
#include "Malon.h"
#include "SoundMgr.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CTerrainObjMgr::Get_Instance()->Initialize(SC_LINKHOME_STAGE);

	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	if (0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	else
		//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(358, 793));
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(358, 793);

	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CGrandpa>::Create(1275, 750));

	/*for (int i = 0; i < 3; ++i)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(float(rand() % WINCX), float(rand() % WINCY)));
	}*/
	if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_UI).size())
	{
		//인벤토리 추가
		CInventoryMgr::Get_Instance()->Initialize();

		//아이템 추가
		//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX + 100, STARTAREA_SHIELD_SPAWNY, BOW, L"BowInven"));
		//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX, STARTAREA_SHIELD_SPAWNY, SHIELD, L"ShieldInven"));
		//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX + 200, STARTAREA_SHIELD_SPAWNY, BOOMERANG, L"BoomerangInven"));
		//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SWORD_SPAWNX, STARTAREA_SWORD_SPAWNY, SWORD, L"SwordInven"));
		//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX + 400, STARTAREA_SHIELD_SPAWNY, STAFF, L"StaffInven"));

		//static_cast<CItem*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM).back())->Set_ItemCode(SWORD);

		//UI 추가


		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create());
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create(HEART_UI_POSX + HEART_UI_CX, HEART_UI_POSY));
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create(HEART_UI_POSX + HEART_UI_CX * 2.f, HEART_UI_POSY));
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create(HEART_UI_POSX + HEART_UI_CX * 3.f, HEART_UI_POSY));
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create(HEART_UI_POSX + HEART_UI_CX * 4.f, HEART_UI_POSY));

		CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create(ITEM_BUTTON_UI_POSX - OVERRAY_WEAPON_UI_CX * 1.f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
		//static_cast<COverrayWeaponUI*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_OVERRAY_UI).back())->ChangeWeapon(static_cast<CItem*>(CInventoryMgr::Get_Instance()->Get_ItemSlotQ())->Get_ItemCode());
		CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create(ITEM_BUTTON_UI_POSX + OVERRAY_WEAPON_UI_CX * 0.5f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CItemButtonUI>::Create());
		//static_cast<COverrayWeaponUI*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_OVERRAY_UI).back())->ChangeWeapon(static_cast<CItem*>(CInventoryMgr::Get_Instance()->Get_ItemSlotW())->Get_ItemCode());
		//HPUI 컨트롤할 매니저
		CHeartUIMgr::Get_Instance()->Initialize();

	}
	CTextBoxMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"House.wav", 0.5f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/LinkHouse.bmp", L"House");

}

int CStage::Update()
{
	CInventoryMgr::Get_Instance()->Update();
	CTextBoxMgr::Get_Instance()->Update();

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory() /*&& false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON() && false == CRSPMgr::Get_Instance()->Get_IsRSPOpen()*/)//
	{
		CTerrainObjMgr::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
	}
	return 0;
}

void CStage::Late_Update()
{
	CInventoryMgr::Get_Instance()->Late_Update();
	CTextBoxMgr::Get_Instance()->Late_Update();

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())// && false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON()
	{
		CObj* Temp = CCollisionMgr::Collision_Player_Door(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DOOR));
		if (Temp != nullptr)
		{
			SCENEID eNextSceneID = static_cast<CDoor*>(Temp)->Get_NextScene();
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
			CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_WALL);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_DOOR);
			CSceneMgr::Get_Instance()->Scene_Change(eNextSceneID);
		}
		CTerrainObjMgr::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		CHeartUIMgr::Get_Instance()->Late_Update();

	}
	
}

void CStage::Render(HDC hDC)
{
	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"House");

		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		BitBlt(hDC, iScrollX, iScrollY, 1440, 960, hGroundDC, 0, 0, SRCCOPY);

		CObjMgr::Get_Instance()->Render(hDC);
		CTextBoxMgr::Get_Instance()->Render(hDC);
		if (true == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
			CTextBoxMgr::Get_Instance()->Render(hDC);
	}
	else if (true == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
		CInventoryMgr::Get_Instance()->Render(hDC);
}

void CStage::Release()
{
}
