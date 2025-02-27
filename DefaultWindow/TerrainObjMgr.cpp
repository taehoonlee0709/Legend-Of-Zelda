#include "stdafx.h"
#include "TerrainObjMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Wall.h"
#include "Door.h"
#include "LinkHomeDoor1.h"
#include "LinkHomeDoor2.h"
#include "MovableStone.h"
#include "Brazier.h"
#include "PressureButton.h"
#include "Road.h"
#include "DungeonDoor.h"
#include "DungeonDoorFrame1.h"
#include "DungeonDoorFrame2.h"
#include "DungeonDoorFrame3.h"
#include "DungeonDoorFrame4.h"
#include "DungeonDoorFrame5.h"
#include "VillageDoorFrame1.h"
#include "VillageDoorFrame2.h"
#include "VillageDoorFrame3.h"
#include "DoorBlock.h"
#include "BigStone.h"



CTerrainObjMgr* CTerrainObjMgr::m_pInstance = nullptr;

CTerrainObjMgr::CTerrainObjMgr() : m_eCurrentTerrainObj(TOBJ_WALL), m_eDoorSceneID(SC_LINKHOME_STAGE)
{
	ZeroMemory(m_tLTRBPoint, sizeof(m_tLTRBPoint));

}

CTerrainObjMgr::~CTerrainObjMgr()
{
	Release();
}

void CTerrainObjMgr::Initialize(SCENEID _eSceneId)
{
	Load_Object(_eSceneId);
}

int CTerrainObjMgr::Update()
{

	Key_Input();

	for (size_t i = 0; i < TERRAINOBJID_END; ++i)
	{
		for (auto& iter : m_TerrainObjList[i])
		{
			iter->Update();

			if (m_TerrainObjList[i].empty())
				break;

		}
	}

	return 0;
}

void CTerrainObjMgr::Late_Update()
{

	for (size_t i = 0; i < TERRAINOBJID_END; ++i)
	{
		for (auto& iter : m_TerrainObjList[i])
		{
			iter->Late_Update();

			if (m_TerrainObjList[i].empty())
				break;

			if (SC_EDIT != CSceneMgr::Get_Instance()->Get_Scene())
			{
				RENDERID	eID = iter->Get_RenderID();
				CObjMgr::Get_Instance()->PushBack_RenderList(eID, iter);
			}



		}
	}
	if (SC_EDIT != CSceneMgr::Get_Instance()->Get_Scene())
	{
		CCollisionMgr::Collision_Obj_Wall(CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER), m_TerrainObjList[TOBJ_WALL]);
		CCollisionMgr::Collision_Obj_Wall(CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER), m_TerrainObjList[TOBJ_WALL]);
		CCollisionMgr::Collision_Obj_Wall(m_TerrainObjList[TOBJ_MOVABLE_STONE], m_TerrainObjList[TOBJ_WALL]);
	}
}

void CTerrainObjMgr::Render(HDC hDC)
{
	if (SC_EDIT == CSceneMgr::Get_Instance()->Get_Scene())
	{
		for (size_t i = 0; i < TERRAINOBJID_END; ++i)
		{
			/*m_RenderList[i].sort(
				[](CObj* pDst, CObj* pSrc)->bool
				{
					return pDst->Get_Info().fY < pSrc->Get_Info().fY;
				});*/

			for (auto& iter : m_TerrainObjList[i])
			{
				iter->Render(hDC);
			}

			//m_RenderList[i].clear();
		}
	}
}

void CTerrainObjMgr::Release()
{
	for (size_t i = 0; i < TERRAINOBJID_END; ++i)
	{
		for_each(m_TerrainObjList[i].begin(), m_TerrainObjList[i].end(), CDeleteObj());
		m_TerrainObjList[i].clear();
	}
}

void CTerrainObjMgr::Add_Object(TERRAINOBJID eID, CObj* pMapObj)
{
	if (TERRAINOBJID_END <= eID || nullptr == pMapObj)
		return;

	m_TerrainObjList[eID].push_back(pMapObj);
}

void CTerrainObjMgr::Delete_Back_TerrainObj()
{
	if (m_TerrainObjList[m_eCurrentTerrainObj].size() > 0)
	{
		auto iter = m_TerrainObjList[m_eCurrentTerrainObj].end();
		--iter;
		delete (*iter);
		(*iter) = nullptr;
		m_TerrainObjList[m_eCurrentTerrainObj].erase(iter);
		MessageBox(g_hWnd, _T("삭제작업"), _T("맵 오브젝트 삭제 성공"), MB_OK);
	}
}

void CTerrainObjMgr::Delete_ID(TERRAINOBJID eID)
{
	for (auto& iter : m_TerrainObjList[eID])
		Safe_Delete(iter);

	m_TerrainObjList[eID].clear();
}




void CTerrainObjMgr::Key_Input()
{


	if (SC_EDIT != CSceneMgr::Get_Instance()->Get_Scene())
		return;


	POINT	ptMouse{};

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	ptMouse.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (TOBJ_WALL == m_eCurrentTerrainObj || TOBJ_DOOR == m_eCurrentTerrainObj)
		{
			// 최초에 클릭했을 때
			if (!m_tLTRBPoint[LEFTTOP].fX && !m_tLTRBPoint[LEFTTOP].fY)
			{
				m_tLTRBPoint[LEFTTOP].fX = (float)ptMouse.x;
				m_tLTRBPoint[LEFTTOP].fY = (float)ptMouse.y;
			}
			else
			{
				m_tLTRBPoint[RIGHTBOTTOM].fX = (float)ptMouse.x;
				m_tLTRBPoint[RIGHTBOTTOM].fY = (float)ptMouse.y;

				if (TOBJ_WALL == m_eCurrentTerrainObj)
					m_TerrainObjList[TOBJ_WALL].push_back(new CWall(m_tLTRBPoint[LEFTTOP], m_tLTRBPoint[RIGHTBOTTOM]));
				else if (TOBJ_DOOR == m_eCurrentTerrainObj)
				{
					m_TerrainObjList[TOBJ_DOOR].push_back(new CDoor(m_tLTRBPoint[LEFTTOP], m_tLTRBPoint[RIGHTBOTTOM]));
					static_cast<CDoor*>(m_TerrainObjList[TOBJ_DOOR].back())->Set_NextScene(m_eDoorSceneID);
				}

				m_tLTRBPoint[LEFTTOP].fX = 0;
				m_tLTRBPoint[LEFTTOP].fY = 0;
				m_tLTRBPoint[RIGHTBOTTOM].fX = 0;
				m_tLTRBPoint[RIGHTBOTTOM].fY = 0;
			}
		}
		else if (TOBJ_LINK_HOME_DOOR1 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_LINK_HOME_DOOR1].push_back(CAbstractFactory<CLinkHomeDoor1>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_LINK_HOME_DOOR2 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_LINK_HOME_DOOR2].push_back(CAbstractFactory<CLinkHomeDoor2>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_MOVABLE_STONE == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_MOVABLE_STONE].push_back(CAbstractFactory<CMovableStone>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_PRESSURE_BUTTON == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_PRESSURE_BUTTON].push_back(CAbstractFactory<CPressureButton>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_BRAZIER == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_BRAZIER].push_back(CAbstractFactory<CBrazier>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_ROAD == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_ROAD].push_back(CAbstractFactory<CRoad>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_DUNGEON_DOOR == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_DUNGEON_DOOR].push_back(CAbstractFactory<CDungeonDoor>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_DUNGEON_DOOR_FRAME1 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_DUNGEON_DOOR_FRAME1].push_back(CAbstractFactory<CDungeonDoorFrame1>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_DUNGEON_DOOR_FRAME2 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_DUNGEON_DOOR_FRAME2].push_back(CAbstractFactory<CDungeonDoorFrame2>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_DUNGEON_DOOR_FRAME3 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_DUNGEON_DOOR_FRAME3].push_back(CAbstractFactory<CDungeonDoorFrame3>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_DUNGEON_DOOR_FRAME4 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_DUNGEON_DOOR_FRAME4].push_back(CAbstractFactory<CDungeonDoorFrame4>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_DUNGEON_DOOR_FRAME5 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_DUNGEON_DOOR_FRAME5].push_back(CAbstractFactory<CDungeonDoorFrame5>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_TOWN_DOOR_FRAME1 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_TOWN_DOOR_FRAME1].push_back(CAbstractFactory<CVillageDoorFrame1>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_TOWN_DOOR_FRAME2 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_TOWN_DOOR_FRAME2].push_back(CAbstractFactory<CVillageDoorFrame2>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_TOWN_DOOR_FRAME3 == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_TOWN_DOOR_FRAME3].push_back(CAbstractFactory<CVillageDoorFrame3>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_PUZZLE_STAGE_BLOCK == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_PUZZLE_STAGE_BLOCK].push_back(CAbstractFactory<CDoorBlock>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		else if (TOBJ_BIG_STONE == m_eCurrentTerrainObj)
		{
			m_TerrainObjList[TOBJ_BIG_STONE].push_back(CAbstractFactory<CBigStone>::Create((float)ptMouse.x, (float)ptMouse.y));
		}
		//else if (MOBJ_WALL == m_eCurrentMapObj)
		//{

		//}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		m_tLTRBPoint[LEFTTOP].fX = 0;
		m_tLTRBPoint[LEFTTOP].fY = 0;
		m_tLTRBPoint[RIGHTBOTTOM].fX = 0;
		m_tLTRBPoint[RIGHTBOTTOM].fY = 0;
	}



	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		Save_Object(SC_EDIT);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Z')) // 현재 선택된 오브젝트리스트의 가장 마지막으로 그린 오브젝트가 삭제됨.
	{
		Delete_Back_TerrainObj();
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		Set_CurrentTerrainObj(TOBJ_WALL);
		MessageBox(g_hWnd, _T("벽"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		Set_CurrentTerrainObj(TOBJ_DOOR);
		MessageBox(g_hWnd, _T("문"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		Set_CurrentTerrainObj(TOBJ_LINK_HOME_DOOR1);
		MessageBox(g_hWnd, _T("링크 집문1"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		Set_CurrentTerrainObj(TOBJ_LINK_HOME_DOOR2);
		MessageBox(g_hWnd, _T("링크 집문2"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('T'))
	{
		Set_CurrentTerrainObj(TOBJ_BRAZIER);
		MessageBox(g_hWnd, _T("화로"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Y'))
	{
		Set_CurrentTerrainObj(TOBJ_ROAD);
		MessageBox(g_hWnd, _T("길"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('U'))
	{
		Set_CurrentTerrainObj(TOBJ_DUNGEON_DOOR);
		MessageBox(g_hWnd, _T("던전 문"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		Set_CurrentTerrainObj(TOBJ_BIG_STONE);
		MessageBox(g_hWnd, _T("큰 돌"), _T("선택 오브젝트"), MB_OK);
	}
	/*else if (CKeyMgr::Get_Instance()->Key_Down('I'))
	{
		Set_CurrentTerrainObj(TOBJ_DUNGEON_DOOR_FRAME1);
		MessageBox(g_hWnd, _T("던전 문틀 1"), _T("선택 오브젝트"), MB_OK);
	}*/
	else if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{
		Set_CurrentTerrainObj(TOBJ_DUNGEON_DOOR_FRAME2);
		MessageBox(g_hWnd, _T("던전 문틀 2"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		Set_CurrentTerrainObj(TOBJ_DUNGEON_DOOR_FRAME3);
		MessageBox(g_hWnd, _T("던전 문틀 3"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		Set_CurrentTerrainObj(TOBJ_DUNGEON_DOOR_FRAME4);
		MessageBox(g_hWnd, _T("던전 문틀 4"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Set_CurrentTerrainObj(TOBJ_DUNGEON_DOOR_FRAME5);
		MessageBox(g_hWnd, _T("던전 문틀 5"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		Set_CurrentTerrainObj(TOBJ_TOWN_DOOR_FRAME1);
		MessageBox(g_hWnd, _T("타운 문틀 1"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('F'))
	{
		Set_CurrentTerrainObj(TOBJ_TOWN_DOOR_FRAME2);
		MessageBox(g_hWnd, _T("타운 문틀 2"), _T("선택 오브젝트"), MB_OK);
	}
	/*else if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		Set_CurrentTerrainObj(TOBJ_TOWN_DOOR_FRAME3);
		MessageBox(g_hWnd, _T("타운 문틀 3"), _T("선택 오브젝트"), MB_OK);
	}*/
	else if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		Set_CurrentTerrainObj(TOBJ_PUZZLE_STAGE_BLOCK);
		MessageBox(g_hWnd, _T("던전블락"), _T("선택 오브젝트"), MB_OK);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down('H'))
	{
		Set_CurrentTerrainObj(TOBJ_MOVABLE_STONE);
		MessageBox(g_hWnd, _T("움직일수 있는 돌"), _T("선택 오브젝트"), MB_OK);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('J'))
	{
		Set_CurrentTerrainObj(TOBJ_PRESSURE_BUTTON);
		MessageBox(g_hWnd, _T("압력 버튼"), _T("선택 오브젝트"), MB_OK);
	}
	if (TOBJ_DOOR == m_eCurrentTerrainObj)
	{
		if (CKeyMgr::Get_Instance()->Key_Down('V'))
		{
			m_eDoorSceneID = SC_LINKHOME_STAGE;
			MessageBox(g_hWnd, _T("링크 집"), _T("문 씬 아이디"), MB_OK);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('B'))
		{
			m_eDoorSceneID = SC_BOSS_STAGE;
			MessageBox(g_hWnd, _T("보스스테이지"), _T("문 씬 아이디"), MB_OK);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('N'))
		{
			m_eDoorSceneID = SC_PUZZLE_STAGE;
			MessageBox(g_hWnd, _T("퍼즐스테이지"), _T("문 씬 아이디"), MB_OK);
		}
		/*else if (CKeyMgr::Get_Instance()->Key_Down('M'))
		{
			m_eDoorSceneID = SC_VILLAGE_STAGE;
			MessageBox(g_hWnd, _T("마을스테이지"), _T("문 씬 아이디"), MB_OK);
		}*/
		else if (CKeyMgr::Get_Instance()->Key_Down('1'))
		{
			m_eDoorSceneID = SC_FIRST_STAGE;
			MessageBox(g_hWnd, _T("첫스테이지"), _T("문 씬 아이디"), MB_OK);
		}
		else if (CKeyMgr::Get_Instance()->Key_Down('M'))
		{
			m_eDoorSceneID = SC_FINAL_STAGE;
			MessageBox(g_hWnd, _T("마지막스테이지"), _T("문 씬 아이디"), MB_OK);
		}
	}

}

void CTerrainObjMgr::Load_Object(SCENEID _eSceneId)
{

	TCHAR* szFileName = L"";

	if (SC_LINKHOME_STAGE == _eSceneId)
		szFileName = L"../Data/LinkHome.dat";
	else if (SC_FIRST_STAGE == _eSceneId)
		szFileName = L"../Data/FirstStage.dat";
	else if (SC_VILLAGE_STAGE == _eSceneId)
		szFileName = L"../Data/VillageStage.dat";
	else if (SC_BOSS_STAGE == _eSceneId)
		szFileName = L"../Data/BossStage.dat";
	else if (SC_PUZZLE_STAGE == _eSceneId)
		szFileName = L"../Data/PuzzleStage.dat";
	else if (SC_CASTLE_STAGE == _eSceneId)
		szFileName = L"../Data/CastleStage.dat";
	else if (SC_FINAL_STAGE == _eSceneId)
		szFileName = L"../Data/FinalStage.dat";
	else if (SC_EDIT == _eSceneId)
		szFileName = L"../Data/1.dat"; //수정하고싶은 맵 주소.

	HANDLE		hFile = CreateFile(szFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return;

	INFO	tInfo{};
	SCENEID  eId(SC_END);
	//int		iDrawID(0), iOption(0);
	int i(0);
	DWORD	dwByte(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &i, sizeof(int), &dwByte, nullptr);
		//ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		//ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pTerrainObj = nullptr;

		if (i == TOBJ_WALL)
			pTerrainObj = CAbstractFactory<CWall>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DOOR)
		{
			ReadFile(hFile, &eId, sizeof(SCENEID), &dwByte, nullptr);

			pTerrainObj = CAbstractFactory<CDoor>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
			static_cast<CDoor*>(pTerrainObj)->Set_NextScene(eId);
		}
		else if (i == TOBJ_LINK_HOME_DOOR1)
			pTerrainObj = CAbstractFactory<CLinkHomeDoor1>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_LINK_HOME_DOOR2)
			pTerrainObj = CAbstractFactory<CLinkHomeDoor2>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_MOVABLE_STONE)
			pTerrainObj = CAbstractFactory<CMovableStone>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_PRESSURE_BUTTON)
			pTerrainObj = CAbstractFactory<CPressureButton>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_BRAZIER)
			pTerrainObj = CAbstractFactory<CBrazier>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_ROAD)
			pTerrainObj = CAbstractFactory<CRoad>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DUNGEON_DOOR)
			pTerrainObj = CAbstractFactory<CDungeonDoor>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DUNGEON_DOOR_FRAME1)
			pTerrainObj = CAbstractFactory<CDungeonDoorFrame1>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DUNGEON_DOOR_FRAME2)
			pTerrainObj = CAbstractFactory<CDungeonDoorFrame2>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DUNGEON_DOOR_FRAME3)
			pTerrainObj = CAbstractFactory<CDungeonDoorFrame3>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DUNGEON_DOOR_FRAME4)
			pTerrainObj = CAbstractFactory<CDungeonDoorFrame4>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_DUNGEON_DOOR_FRAME5)
			pTerrainObj = CAbstractFactory<CDungeonDoorFrame5>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_TOWN_DOOR_FRAME1)
			pTerrainObj = CAbstractFactory<CVillageDoorFrame1>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_TOWN_DOOR_FRAME2)
			pTerrainObj = CAbstractFactory<CVillageDoorFrame2>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_TOWN_DOOR_FRAME3)
			pTerrainObj = CAbstractFactory<CVillageDoorFrame3>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_PUZZLE_STAGE_BLOCK)
			pTerrainObj = CAbstractFactory<CDoorBlock>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		else if (i == TOBJ_BIG_STONE)
			pTerrainObj = CAbstractFactory<CBigStone>::Create(tInfo.fX, tInfo.fY, tInfo.fCX, tInfo.fCY);
		//dynamic_cast<CWall*>(pMapObj)->Set_Tile(iDrawID, iOption);

		m_TerrainObjList[i].push_back(pTerrainObj); //여기서 문제 터짐.
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("불러오기 성공"), _T("성공"), MB_OK);
}

void CTerrainObjMgr::Save_Object(SCENEID _eSceneId)
{
	TCHAR* szFileName = L"../Data/SaveTerrainObj.dat"; //수정하고싶은 맵 주소

	//if (SC_STAGE == _eSceneId)
	//	szFileName = L"../Data/StartArea.dat";
	//else if (SC_BOSS_STAGE == _eSceneId)
	//	szFileName = L"../Data/BossStage.dat";
	//else if (SC_EDIT == _eSceneId)
	//szFileName = .
		//szFileName = L"../Data/StartArea.dat";
	HANDLE		hFile = CreateFile(szFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	//int		iDrawID(0), iOption(0);
	//MAPOBJID	eID(MAPOBJID_END);
	DWORD	dwByte(0);

	for (size_t i = 0; TERRAINOBJID_END > i; ++i)
	{
		for (auto& iter : m_TerrainObjList[i])
		{
			//iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
			//iOption = dynamic_cast<CTile*>(iter)->Get_Option();

			WriteFile(hFile, &(iter->Get_Info()), sizeof(INFO), &dwByte, nullptr);
			WriteFile(hFile, &i, sizeof(int), &dwByte, nullptr);
			if (i == TOBJ_DOOR)
			{
				SCENEID eId = static_cast<CDoor*>(iter)->Get_NextScene();
				WriteFile(hFile, &(eId), sizeof(SCENEID), &dwByte, nullptr);
			}
			//WriteFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);
		}
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("맵오브젝트 저장"), _T("맵오브젝트 저장 성공"), MB_OK);
}
