#include "stdafx.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CScrollMgr*	CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	int ScreenCX(0), ScreenCY(0);

	if (0.f < m_fScrollX)
	{
		m_fScrollX = 0.f;
	}

	if (0.f < m_fScrollY)
	{
		m_fScrollY = 0.f;
	}
	if (SC_LINKHOME_STAGE == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 1440;
		ScreenCY = 960;
	}
	else if (SC_EDIT == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 6000;
		ScreenCY = 6000;
	}
	else if (SC_FIRST_STAGE == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 3024;
		ScreenCY = 2064;
	}
	else if (SC_VILLAGE_STAGE == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 2208;
		ScreenCY = 2818;
	}
	else if (SC_PUZZLE_STAGE == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 1776;
		ScreenCY = 5232;
	}
	else if (SC_BOSS_STAGE == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 1216;
		ScreenCY = 896;
	}
	else if (SC_FINAL_STAGE == CSceneMgr::Get_Instance()->Get_Scene())
	{
		ScreenCX = 761;
		ScreenCY = 1200;
	}
	if (WINCX - ScreenCX > m_fScrollX)
		m_fScrollX = WINCX - ScreenCX;

	if (WINCY - ScreenCY > m_fScrollY)
		m_fScrollY = WINCY - ScreenCY;

}
