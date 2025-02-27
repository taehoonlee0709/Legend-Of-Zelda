#include "stdafx.h"
#include "BigStone.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

void CBigStone::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/BigStone.bmp", L"BigStone");
	m_pFrameKey = L"BigStone";
	m_tInfo.fCX = BIG_STONE_CX;
	m_tInfo.fCY = BIG_STONE_CY;
	//m_fSpeed = 4.f;
	m_eRender = RENDER_GAMEOBJECT;

	//m_dwDelayTime = GetTickCount() + (DWORD)STAFF_BULLET_DELAY;
	m_bInvincibility = false; //보이고 못가는 상태

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CBigStone::Update()
{
	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CBigStone::Late_Update()
{
	if (m_bInvincibility == false)
		CollisionPlayer();

	if (m_bInvincibility == false)
		m_tFrame.iFrameStart = 0;
	else
		m_tFrame.iFrameStart = 1;
}

void CBigStone::Render(HDC hDC)
{
	/*if (SC_EDIT == CSceneMgr::Get_Instance()->Get_CurSceneId())
		m_tFrame.iFrameStart = 0;*/

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // 복사 받을 위치 x, y 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,		// 복사할 이미지 dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
		(int)m_tInfo.fCX,	// 복사할 이미지의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(160, 0, 96));	// 제거하고자 하는 색상값
}

void CBigStone::Release()
{
}

void CBigStone::CollisionPlayer()
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