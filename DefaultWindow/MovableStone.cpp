#include "stdafx.h"
#include "MovableStone.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

void CMovableStone::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/MovableStone.bmp", L"MovableStone");
	m_pFrameKey = L"MovableStone";
	m_tInfo.fCX = MOVABLE_STONE_CX;
	m_tInfo.fCY = MOVABLE_STONE_CY;
	//m_fSpeed = 4.f;
	m_eRender = RENDER_GAMEOBJECT;

	//m_dwDelayTime = GetTickCount() + (DWORD)STAFF_BULLET_DELAY;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 1000;
}

int CMovableStone::Update()
{

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMovableStone::Late_Update()
{
	CollisionPlayer();
	
}

void CMovableStone::Render(HDC hDC)
{
	__super::Update_Rect();
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	BitBlt(hDC, 
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY, 
		(int)MOVABLE_STONE_CX, 
		(int)MOVABLE_STONE_CY, 
		hMemDC, 
		0, 
		0, 
		SRCCOPY);
}
	

void CMovableStone::Release()
{
}

void CMovableStone::CollisionPlayer()
{
	if (0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
		return;
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	float	fX(0.f), fY(0.f);


	if (CCollisionMgr::Check_Rect(this, pPlayer, &fX, &fY))
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MAPOBJECT);
		CSoundMgr::Get_Instance()->PlaySound(L"MovableStone.wav", SOUND_MAPOBJECT,1.f);
		// 상하 충돌
		if (fX > fY)
		{
			// 상 충돌
			if (this->Get_Info().fY < pPlayer->Get_Info().fY)
			{
				this->Set_PosY(-fY*0.2f);
				pPlayer->Set_PosY(fY * 0.8f);
			}

			else
			{
				this->Set_PosY(fY * 0.2f);
				pPlayer->Set_PosY(-fY * 0.8f);
			}
		}
		// 좌우 충돌
		else
		{
			// 좌 충돌
			if (this->Get_Info().fX < pPlayer->Get_Info().fX)
			{
				this->Set_PosX(-fX * 0.2f);
				pPlayer->Set_PosX(fX * 0.8f);
			}

			// 우 충돌
			else
			{
				this->Set_PosX(fX * 0.2f);
				pPlayer->Set_PosX(-fX * 0.8f);
			}
		}

	}
}
