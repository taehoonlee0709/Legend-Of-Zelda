#include "stdafx.h"
#include "PuzzleStage.h"
#include "stdafx.h"
#include "PuzzleStage.h"
#include "TerrainObjMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "PuzzleMgr.h"
#include "CollisionMgr.h"
#include "Door.h"
#include "SceneMgr.h"
#include "InventoryMgr.h"
#include "HeartUIMgr.h"
#include "TextBoxMgr.h"
#include "Snake.h"
#include "Octorock.h"
#include "Moblin.h"

void CPuzzleStage::Initialize()
{
	CTerrainObjMgr::Get_Instance()->Initialize(SC_PUZZLE_STAGE);
	CPuzzleMgr::Get_Instance()->Initialize();


	//플레이어 추가
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(PUZZLE_STAGE_PLAYER_SPAWNX, PUZZLE_STAGE_PLAYER_SPAWNY);
	//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create_Obj(PUZZLE_STAGE_PLAYER_SPAWNX, PUZZLE_STAGE_PLAYER_SPAWNY));
	//UI 추가
	/*CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj());
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX, HEART_UI_POSY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX * 2.f, HEART_UI_POSY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CHeartUI>::Create_Obj(HEART_UI_POSX + HEART_UI_CX * 3.f, HEART_UI_POSY));
	CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CItemButtonUI>::Create_Obj());
	CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create_Obj(ITEM_BUTTON_UI_POSX - OVERRAY_WEAPON_UI_CX * 1.5f, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_OVERRAY_UI, CAbstractFactory<COverrayWeaponUI>::Create_Obj(ITEM_BUTTON_UI_POSX, ITEM_BUTTON_UI_POSY - OVERRAY_WEAPON_UI_CY * 0.1f));
	*/
	//몬스터 추가
	//1구역 스네이크
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(PUZZLE_STAGE_SECTION1_SNAKE_SPAWNX, PUZZLE_STAGE_SECTION1_SNAKE_SPAWNY));
	//2구역 스네이크들
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(680, 1185));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(680, 1405));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1080, 1185));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CSnake>::Create(1080, 1405));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COctorock>::Create(720, 4058));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COctorock>::Create(PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNX - OCTOROK_BLUE_COLLISION_CX, PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNY + OCTOROK_BLUE_COLLISION_CY));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<COctorock>::Create(PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNX - OCTOROK_BLUE_COLLISION_CX * 2, PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNY + OCTOROK_BLUE_COLLISION_CY * 2));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_OCTOROK, CAbstractFactory<COctorokBlue>::Create_Obj(PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNX - OCTOROK_BLUE_COLLISION_CX * 3, PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNY + OCTOROK_BLUE_COLLISION_CY * 3));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMoblin>::Create(405, 225));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMoblin>::Create(1375, 225));


	//사운드 추가
	CSoundMgr::Get_Instance()->PlayBGM(L"PuzzleStage.wav", 0.5f);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/PuzzleStage.bmp", L"PuzzleStage");
}

int CPuzzleStage::Update()
{
	CInventoryMgr::Get_Instance()->Update();
	//CTextBoxMgr::Get_Instance()->Update();

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		CPuzzleMgr::Get_Instance()->Update();
		CTerrainObjMgr::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
	}


	return 0;
}

void CPuzzleStage::Late_Update()
{
	CInventoryMgr::Get_Instance()->Late_Update();

	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		CObj* Temp = CCollisionMgr::Collision_Player_Door(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DOOR));
		if (Temp != nullptr)
		{
			SCENEID eNextSceneID = static_cast<CDoor*>(Temp)->Get_NextScene();
			CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
			CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_WALL);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_DOOR);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_BRAZIER);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_MOVABLE_STONE);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_PRESSURE_BUTTON);
			CTerrainObjMgr::Get_Instance()->Delete_ID(TOBJ_ROAD);
			CSceneMgr::Get_Instance()->Scene_Change(eNextSceneID);
		}

		CTerrainObjMgr::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
		CHeartUIMgr::Get_Instance()->Late_Update();
		CPuzzleMgr::Get_Instance()->Late_Update();
	}


}

void CPuzzleStage::Render(HDC hDC)
{
	if (false == CInventoryMgr::Get_Instance()->Get_IsOpenInventory())
	{
		HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"PuzzleStage");

		int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		BitBlt(hDC, iScrollX, iScrollY, PUZZLE_STAGE_MAX_SCREENX, PUZZLE_STAGE_MAX_SCREENY, hGroundDC, 0, 0, SRCCOPY);

		//CLineMgr::Get_Instance()->Render(hDC);

		CObjMgr::Get_Instance()->Render(hDC);
	}
	else
		CInventoryMgr::Get_Instance()->Render(hDC);


}

void CPuzzleStage::Release()
{
}
