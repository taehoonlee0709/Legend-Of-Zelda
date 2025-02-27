#include "stdafx.h"
#include "Door.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "TerrainObjMgr.h"

CDoor::CDoor(LINEPOINT& tLTPoint, LINEPOINT& tRBPoint)
{
	m_tInfo = { (tLTPoint.fX + tRBPoint.fX) * 0.5f ,(tLTPoint.fY + tRBPoint.fY) * 0.5f, abs(tLTPoint.fX - tRBPoint.fX), abs(tLTPoint.fY - tRBPoint.fY) };

}

void CDoor::Initialize()
{
	m_eRender = RENDER_BACKGROUND;
}

int CDoor::Update()
{
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CDoor::Late_Update()
{
}

void CDoor::Render(HDC hDC)
{
	/*int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);*/
}

void CDoor::Release()
{
}
