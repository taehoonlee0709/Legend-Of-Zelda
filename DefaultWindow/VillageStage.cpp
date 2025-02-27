#include "stdafx.h"
#include "VillageStage.h"


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
#include "OverrayWeaponUI.h"
#include "ItemButtonUI.h"
#include "Octorock.h"
#include "HeartUIMgr.h"
#include "Malon.h"
#include "Terry.h"
#include "TextBoxMgr.h"
#include "Uncle.h"
#include "SoundMgr.h"
#include "RSPMgr.h"
#include "CoinMgr.h"


CVillageStage::CVillageStage()
{
}


CVillageStage::~CVillageStage()
{
	Release();
}

void CVillageStage::Initialize()
{
	CTerrainObjMgr::Get_Instance()->Initialize(SC_VILLAGE_STAGE);
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(740, 2700);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/VillageStage.bmp", L"VillageStage");

	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());



	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CMalon>::Create(845, 1714));
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CTerry>::Create(845, 1480));
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CUncle>::Create(610, 1480));

	/*CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1400, 1600));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1400, 1400));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1400, 1200));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1400, 1000));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COctorock>::Create(2700, 1000));*/

	/*if (!CObjMgr::Get_Instance()->Get_ObjList(OBJ_UI).size())
	{*/
	//인벤토리 추가
	//CInventoryMgr::Get_Instance()->Initialize();

	//아이템 추가
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX + 100, STARTAREA_SHIELD_SPAWNY, BOW, L"BowInven"));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX, STARTAREA_SHIELD_SPAWNY, SHIELD, L"ShieldInven"));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX + 200, STARTAREA_SHIELD_SPAWNY, BOOMERANG, L"BoomerangInven"));
	/*CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(1970, 1460, SWORD, L"SwordInven"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(1970, 1760, WAND, L"StaffInven"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(1670, 1760, BOOMERANG, L"BoomerangInven"));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(1570, 1760, SHIELD, L"ShieldInven"));*/

	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(STARTAREA_SHIELD_SPAWNX + 400, STARTAREA_SHIELD_SPAWNY, STAFF, L"StaffInven"));

	//static_cast<CItem*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_ITEM).back())->Set_ItemCode(SWORD);

	//UI 추가
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Ob());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX, HEART_UI_POSY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX * 2.f, HEART_UI_POSY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX * 3.f, HEART_UI_POSY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CItemButtonUI>::Create());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create(ITEM_BUTTON_UI_POSX - OVERRAY_WEAPON_UI_CX * 1.f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
	////static_cast<COverrayWeaponUI*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_OVERRAY_UI).back())->ChangeWeapon(static_cast<CItem*>(CInventoryMgr::Get_Instance()->Get_ItemSlotQ())->Get_ItemCode());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create(ITEM_BUTTON_UI_POSX + OVERRAY_WEAPON_UI_CX * 0.5f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
	////static_cast<COverrayWeaponUI*>(CObjMgr::Get_Instance()->Get_ObjList(OBJ_OVERRAY_UI).back())->ChangeWeapon(static_cast<CItem*>(CInventoryMgr::Get_Instance()->Get_ItemSlotW())->Get_ItemCode());
	////HPUI 컨트롤할 매니저
	//CHeartUIMgr::Get_Instance()->Initialize();
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create(ITEM_BUTTON_UI_POSX - OVERRAY_WEAPON_UI_CX * 1.f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create(ITEM_BUTTON_UI_POSX + OVERRAY_WEAPON_UI_CX * 0.5f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));

/*}*/
	CSoundMgr::Get_Instance()->PlayBGM(L"TownBgm.wav", 1.f);
	if (0 == CRSPMgr::Get_Instance()->Get_Vector().size())
		CRSPMgr::Get_Instance()->Initialize();
	if (0 == CCoinMgr::Get_Instance()->Get_Vector().size())
		CCoinMgr::Get_Instance()->Initialize();

}

int CVillageStage::Update()
{
	
	CInventoryMgr::Get_Instance()->Update();
	//CObjMgr::Get_Instance()->Update();
	CTextBoxMgr::Get_Instance()->Update();
	CRSPMgr::Get_Instance()->Update();
	CCoinMgr::Get_Instance()->Update();

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory() && false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON() && false == CRSPMgr::Get_Instance()->Get_IsRSPOpen() && false == CCoinMgr::Get_Instance()->Get_IsCoinOpen())
	{
		CObjMgr::Get_Instance()->Update();
		CTerrainObjMgr::Get_Instance()->Update();

	}

	return 0;
}

void CVillageStage::Late_Update()
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
			CObjMgr::Get_Instance()->Delete_ID(OBJ_NPC);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_WALL);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_DOOR);
			CSceneMgr::Get_Instance()->Scene_Change(eNextSceneID);
		}
		CTerrainObjMgr::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		CHeartUIMgr::Get_Instance()->Late_Update();

	}

	//CObjMgr::Get_Instance()->Late_Update();

}

void CVillageStage::Render(HDC hDC)
{
	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory() && false == CRSPMgr::Get_Instance()->Get_IsRSPOpen() && false == CCoinMgr::Get_Instance()->Get_IsCoinOpen())
	{
		HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"VillageStage");

		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		BitBlt(hDC, iScrollX, iScrollY, 2208, 2818, hGroundDC, 0, 0, SRCCOPY);

		//CLineMgr::Get_Instance()->Render(hDC);
		CObjMgr::Get_Instance()->Render(hDC);
	}
	else if (true == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
		CInventoryMgr::Get_Instance()->Render(hDC);
	if (true == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
		CTextBoxMgr::Get_Instance()->Render(hDC);
	else if (true == CRSPMgr::Get_Instance()->Get_IsRSPOpen())
		CRSPMgr::Get_Instance()->Render(hDC);
	else if (true == CCoinMgr::Get_Instance()->Get_IsCoinOpen())
		CCoinMgr::Get_Instance()->Render(hDC);
}

void CVillageStage::Release()
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}