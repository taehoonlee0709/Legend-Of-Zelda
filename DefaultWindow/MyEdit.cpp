#include "stdafx.h"
#include "MyEdit.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TerrainObjMgr.h"
#include "Stage.h"
//#include "BossStage.h"
//#include "TileMgr.h"

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/LinkHouse.bmp", L"EDIT");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FirstStage.bmp", L"EDIT");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/VillageStage.bmp", L"EDIT");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/PuzzleStage.bmp", L"EDIT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/BossStage.bmp", L"EDIT");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/FinalStage.bmp", L"EDIT");

	CTerrainObjMgr::Get_Instance()->Initialize(SC_EDIT);
}

int CMyEdit::Update()
{
	Key_Input();

	CTerrainObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyEdit::Late_Update()
{

	CTerrainObjMgr::Get_Instance()->Late_Update();
	//CTileMgr::Get_Instance()->Late_Update();
}

void CMyEdit::Render(HDC hDC)
{
	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Image(L"EDIT");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//Rectangle(hDC, 0, 0, 800, 600);
	//BitBlt(hDC, iScrollX, iScrollY, EDIT_MAX_SCREENX, EDIT_MAX_SCREENY, hGroundDC, 0, 0, SRCCOPY);
	BitBlt(hDC, iScrollX, iScrollY, 6000, 6000, hGroundDC, 0, 0, SRCCOPY);
	//BitBlt(hDC, iScrollX, iScrollY, 3024, 2064, hGroundDC, 0, 0, SRCCOPY);
	CTerrainObjMgr::Get_Instance()->Render(hDC);
	//CTileMgr::Get_Instance()->Render(hDC);



	//HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"StartArea");

	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//BitBlt(hDC, iScrollX, iScrollY, STARTAREA_MAX_SCREENX, STARTAREA_MAX_SCREENY, hGroundDC, 0, 0, SRCCOPY);

	////CLineMgr::Get_Instance()->Render(hDC);

	//CMapObjMgr::Get_Instance()->Render(hDC);
	////CMapObjMgr::Get_Instance()->Render(hDC);
}

void CMyEdit::Release()
{
}

void CMyEdit::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(15.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-15.f);


}
