#include "stdafx.h"
#include "BossStage.h"
#include "TerrainObjMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Player.h"
#include "HeartUI.h"
#include "ItemButtonUI.h"
#include "OverrayWeaponUI.h"
#include "BossGuhu.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "HeartUIMgr.h"
#include "TextBoxMgr.h"
#include "InventoryMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Door.h"
#include "BossPuzzleMgr.h"

//float g_fBGMSound = 1.f;

CBossStage::CBossStage()
{
}

CBossStage::~CBossStage()
{
	Release();
}

void CBossStage::Initialize()
{
	//CLineMgr::Get_Instance()->Initialize();
	CTerrainObjMgr::Get_Instance()->Initialize(SC_BOSS_STAGE);
	//CBossPuzzleMgr::Get_Instance()->Initialize();


	//플레이어 추가
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj(BOSS_STAGE_PLAYER_SPAWNX, BOSS_STAGE_PLAYER_SPAWNY));
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(BOSS_STAGE_PLAYER_SPAWNX, BOSS_STAGE_PLAYER_SPAWNY);
	//UI 추가
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX, HEART_UI_POSY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX * 2.f, HEART_UI_POSY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX * 3.f, HEART_UI_POSY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CItemButtonUI>::Create_Obj());
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create_Obj(ITEM_BUTTON_UI_POSX - OVERRAY_WEAPON_UI_CX * 1.5f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create_Obj(ITEM_BUTTON_UI_POSX, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));

	//몬스터 추가
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossGuhu>::Create(BOSS_STAGE_MAX_SCREENX * 0.5f, BOSS_STAGE_MAX_SCREENY * 0.4f));

	//사운드 추가
	CSoundMgr::Get_Instance()->PlayBGM(L"BossStageBgm.wav", 0.5f);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossStage.bmp", L"BossStage");
}

int CBossStage::Update()
{

	CInventoryMgr::Get_Instance()->Update();
	CTextBoxMgr::Get_Instance()->Update();

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory() && false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())//
	{
		//CBossPuzzleMgr::Get_Instance()->Update();

		CObjMgr::Get_Instance()->Update();
		CTerrainObjMgr::Get_Instance()->Update();
		
	}

	return 0;
}

void CBossStage::Late_Update()
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
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_WALL);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_DOOR);
			CSceneMgr::Get_Instance()->Scene_Change(eNextSceneID);
		}

		CTerrainObjMgr::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		CHeartUIMgr::Get_Instance()->Late_Update();
		//CBossPuzzleMgr::Get_Instance()->Late_Update();

	}



	//CMapObjMgr::Get_Instance()->Late_Update();
	//CObjMgr::Get_Instance()->Late_Update();
	//CHeartUIMgr::Get_Instance()->Late_Update();
}

void CBossStage::Render(HDC hDC)
{
	//HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"BossStage");

	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, iScrollX, iScrollY, BOSS_STAGE_MAX_SCREENX, BOSS_STAGE_MAX_SCREENY, hGroundDC, 0, 0, SRCCOPY);

	////CLineMgr::Get_Instance()->Render(hDC);

	//CObjMgr::Get_Instance()->Render(hDC);
	//CMapObjMgr::Get_Instance()->Render(hDC);

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"BossStage");

		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		BitBlt(hDC, iScrollX, iScrollY, BOSS_STAGE_MAX_SCREENX, BOSS_STAGE_MAX_SCREENY, hGroundDC, 0, 0, SRCCOPY);

		//CLineMgr::Get_Instance()->Render(hDC);

		CObjMgr::Get_Instance()->Render(hDC);
		//CMapObjMgr::Get_Instance()->Render(hDC);
		CTextBoxMgr::Get_Instance()->Render(hDC);
		if (true == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
			CTextBoxMgr::Get_Instance()->Render(hDC);
	}
	else if (true == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
		CInventoryMgr::Get_Instance()->Render(hDC);
}

void CBossStage::Release()
{
}
