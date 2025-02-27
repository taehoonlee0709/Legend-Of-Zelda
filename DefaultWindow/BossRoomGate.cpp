#include "stdafx.h"
#include "BossRoomGate.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

void CBossRoomGate::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Terrain/BossRoomGate.bmp", L"BossRoomGate");
	m_pFrameKey = L"BossRoomGate";
	m_tInfo.fCX = DUNGEON_DOOR_CX;
	m_tInfo.fCY = DUNGEON_DOOR_CY;
	//m_fSpeed = 4.f;
	m_eRender = RENDER_GAMEOBJECT;

	//m_dwDelayTime = GetTickCount() + (DWORD)STAFF_BULLET_DELAY;
	m_bInvincibility = false; //���̰� ������ ����

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 200;
}

int CBossRoomGate::Update()
{
	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CBossRoomGate::Late_Update()
{
	if (m_bInvincibility == false)
		CollisionPlayer();

	if (m_bInvincibility == false)
		m_tFrame.iFrameStart = 0;
	else
		m_tFrame.iFrameStart = 1;
}

void CBossRoomGate::Render(HDC hDC)
{
	/*if (SC_EDIT == CSceneMgr::Get_Instance()->Get_CurSceneId())
		m_tFrame.iFrameStart = 0;*/

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,		// ������ �̹��� dc
		(int)m_tInfo.fCX * m_tFrame.iFrameStart,
		(int)m_tInfo.fCY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		(int)m_tInfo.fCX,	// ������ �̹����� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
}

void CBossRoomGate::Release()
{
}

void CBossRoomGate::CollisionPlayer()
{
	if (0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
		return;
	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	float	fX(0.f), fY(0.f);


	if (CCollisionMgr::Check_Rect(this, pPlayer, &fX, &fY))
	{
		// ���� �浹
		if (fX > fY)
		{
			// �� �浹
			if (this->Get_Info().fY < pPlayer->Get_Info().fY)
			{
				pPlayer->Set_PosY(fY);
			}

			else
			{

				pPlayer->Set_PosY(-fY);
			}
		}
		// �¿� �浹
		else
		{
			// �� �浹
			if (this->Get_Info().fX < pPlayer->Get_Info().fX)
			{

				pPlayer->Set_PosX(fX);
			}

			// �� �浹
			else
			{

				pPlayer->Set_PosX(-fX);
			}
		}

	}
}
