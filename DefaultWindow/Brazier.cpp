#include "stdafx.h"
#include "Brazier.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "PuzzleMgr.h"
#include "BossPuzzleMgr.h"

void CBrazier::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/BrazierOff.bmp", L"BrazierOff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/BrazierOn.bmp", L"BrazierOn");
	m_pFrameKey = L"BrazierOff";
	m_tInfo.fCX = BRAZIER_CX;
	m_tInfo.fCY = BRAZIER_CY;
	//m_fSpeed = 4.f;
	m_eRender = RENDER_GAMEOBJECT;

	//m_dwDelayTime = GetTickCount() + (DWORD)STAFF_BULLET_DELAY;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CBrazier::Update()
{
	__super::Update_Rect();
	

	return OBJ_NOEVENT;
}

void CBrazier::Late_Update()
{
	if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size() && m_pFrameKey == L"BrazierOff")
	{
		RECT rc{};
		list<CObj*> templist = CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER_BULLET);
		for (auto iter = templist.begin();
			iter != templist.end();
			++iter)
		{
			RECT rc{};
			if (IntersectRect(&rc, &(*iter)->Get_Rect(), &this->Get_Rect()))
			{
				m_pFrameKey = L"BrazierOn";
				ChangeOnOff();
				return;
			}
		}

	}
	CollisionPlayer();
	__super::Move_Frame();
	if (m_pFrameKey == L"BrazierOn")
	{
		CPuzzleMgr::Get_Instance()->Set_TriggerCount();
		CBossPuzzleMgr::Get_Instance()->Set_TriggerCount();

	}
}

void CBrazier::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)BRAZIER_CX,
		(int)BRAZIER_CY,
		hMemDC,
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,
		SRCCOPY);
}

void CBrazier::Release()
{
}

void CBrazier::ChangeOnOff()
{
	if (m_pFrameKey == L"BrazierOff")
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 200;
	}
	else if(m_pFrameKey == L"BrazierOn")
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iMotion = 0;
		m_tFrame.dwTime = GetTickCount();
		m_tFrame.dwSpeed = 100;
	}
}

void CBrazier::CollisionPlayer()
{
	if (0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
		return;
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	float	fX(0.f), fY(0.f);


	if (CCollisionMgr::Check_Rect(this, pPlayer, &fX, &fY))
	{
		// 상하 충돌
		if (fX > fY)
		{
			// 상 충돌
			if (this->Get_Info().fY < pPlayer->Get_Info().fY)
			{
				pPlayer->Set_PosY(fY);
			}

			else
			{

				pPlayer->Set_PosY(-fY);
			}
		}
		// 좌우 충돌
		else
		{
			// 좌 충돌
			if (this->Get_Info().fX < pPlayer->Get_Info().fX)
			{

				pPlayer->Set_PosX(fX);
			}

			// 우 충돌
			else
			{
	
				pPlayer->Set_PosX(-fX);
			}
		}

	}
}
