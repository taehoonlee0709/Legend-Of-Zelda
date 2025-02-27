#pragma once
#include "Define.h"
#include "Obj.h"
#include "TerrainObj.h"

enum POINTPOS { LEFTTOP, RIGHTBOTTOM, POINTPOS_END };

enum TERRAINOBJID {
	TOBJ_WALL, 
	TOBJ_DOOR,
	TOBJ_LINK_HOME_DOOR1,
	TOBJ_LINK_HOME_DOOR2,
	TOBJ_MOVABLE_STONE, 
	TOBJ_PRESSURE_BUTTON, 
	TOBJ_BRAZIER, 
	TOBJ_ROAD, 
	TOBJ_DUNGEON_DOOR,
	TOBJ_DUNGEON_DOOR_FRAME1, 
	TOBJ_DUNGEON_DOOR_FRAME2, 
	TOBJ_DUNGEON_DOOR_FRAME3,
	TOBJ_DUNGEON_DOOR_FRAME4,
	TOBJ_DUNGEON_DOOR_FRAME5,
	TOBJ_TOWN_DOOR_FRAME1, 
	TOBJ_TOWN_DOOR_FRAME2, 
	TOBJ_TOWN_DOOR_FRAME3, 
	TOBJ_PUZZLE_STAGE_BLOCK,
	TOBJ_BIG_STONE,
	TERRAINOBJID_END
};
class CTerrainObjMgr
{
private:
	CTerrainObjMgr();
	~CTerrainObjMgr();


public:
	void		Initialize(SCENEID _eSceneId);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Add_Object(TERRAINOBJID eID, CObj* pTerrainObj);
	void		Delete_Back_TerrainObj();
	void		Delete_ID(TERRAINOBJID eID);

	list<CObj*>	Get_TerrainObjList(TERRAINOBJID _eID) { return m_TerrainObjList[_eID]; }

	void		Key_Input();
	void		Load_Object(SCENEID _eSceneId);
	void		Save_Object(SCENEID _eSceneId);

	void		Set_CurrentTerrainObj(TERRAINOBJID _eID) { m_eCurrentTerrainObj = _eID; }

private:
	list<CObj*>		m_TerrainObjList[TERRAINOBJID_END];
	LINEPOINT		m_tLTRBPoint[POINTPOS_END];
	TERRAINOBJID		m_eCurrentTerrainObj;
	SCENEID			m_eDoorSceneID;


public:
	static CTerrainObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTerrainObjMgr;

		return m_pInstance;
	}
	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CTerrainObjMgr* m_pInstance;
};

