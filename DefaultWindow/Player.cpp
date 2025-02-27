#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "InventoryMgr.h"
#include "SwordBullet.h"
#include "WandBullet.h"
#include "ShieldBullet.h"
#include "BoomerangBullet.h"
#include "HeartUIMgr.h"
#include "SoundMgr.h"
float g_fSound = 1.f;

CPlayer::CPlayer()
	: m_pBullet(nullptr), m_pShield(nullptr)
	, m_eCurState(IDLE), m_ePreState(STATE_END)
	, m_bAction(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 200, 130, 60.f, 60.f };
	m_fSpeed = 5.f;
	m_fDistance = 100.f;
	m_fPower = 20.f;
	m_fTime = 0.f;
	m_fAngle = 90.f;
	m_iHp = 20;


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_DOWN.bmp", L"Player_DOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");

	m_pFrameKey = L"Player_DOWN";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
	m_eRender = RENDER_GAMEOBJECT;

}

int CPlayer::Update()
{

	Key_Input();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	OffSet2();


	__super::Move_Frame();
	Motion_Change();

}

void CPlayer::Render(HDC hDC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(
		hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		(int)(m_tInfo.fX - 200 * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
		(int)(m_tInfo.fY - 200 * 0.5f) + iScrollY,
		200,	// 복사 받을 이미지의 가로, 세로
		200,
		hMemDC,		// 비트맵을 가지고 있는 DC
		200 * m_tFrame.iFrameStart,			// 비트맵 출력 시작 좌표 LEFT, TOP
		200 * m_tFrame.iMotion,
		200,	// 출력할 비트맵 가로
		200,	// 출력할 비트맵 세로
		RGB(163, 13, 169));	// 제거할 색상 값
}

void CPlayer::Release()
{
}

void CPlayer::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (200 * 0.5f));
	m_tRect.top = LONG(m_tInfo.fY - (200 * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (200 * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (200 * 0.5f));
}
void CPlayer::Get_Hit() //언제 히트 판정이 나요? 무적이 아닐때요 그러면 무적이면 이 함수가 돌면 안되요
{
	if (m_bInvincibility)
		return;

	Set_Invincibility();
	m_bAction = true;
	m_eCurState = HIT;
	Set_Hp(-1);
	CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
	CSoundMgr::Get_Instance()->PlaySound(L"PlayerHit.wav", SOUND_PLAYER, g_fSound);
	CHeartUIMgr::Get_Instance()->Minus_Hp();
}
void CPlayer::Get_Item(CObj* _pItem)
{
	m_bAction = true;
	m_eCurState = GET_ITEM;
	Set_Target(_pItem);
	m_pTarget->Set_Pos(m_tInfo.fX, m_tInfo.fY - _pItem->Get_Info().fCY);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"GetItem.wav", SOUND_EFFECT, g_fSound);

}
void CPlayer::Key_Input()
{
	if (m_bAction == true && GetTickCount() > m_tFrame.dwMotionTime)
	{
		m_bAction = false;
		m_eCurState = IDLE;
		if (m_bInvincibility)
			Set_Invincibility();
		if (nullptr != m_pTarget)
		{
			m_pTarget->Set_Dead();
			m_pTarget = nullptr;
		}
	}

	if (m_bAction == false)
	{


		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			{
				m_tInfo.fX -= m_fSpeed / (float)sqrt(2.);
				m_tInfo.fY -= m_fSpeed / (float)sqrt(2.);
			}
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				m_tInfo.fX -= m_fSpeed / (float)sqrt(2.);
				m_tInfo.fY += m_fSpeed / (float)sqrt(2.);
			}
			else
			{
				m_tInfo.fX -= m_fSpeed;
				m_pFrameKey = L"Player_LEFT";
			}
			m_fAngle = 180.f;
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
			{
				m_tInfo.fX += m_fSpeed / (float)sqrt(2.);
				m_tInfo.fY -= m_fSpeed / (float)sqrt(2.);
			}
			else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
			{
				m_tInfo.fX += m_fSpeed / (float)sqrt(2.);
				m_tInfo.fY += m_fSpeed / (float)sqrt(2.);
			}
			else
			{
				m_tInfo.fX += m_fSpeed;
				m_pFrameKey = L"Player_RIGHT";
			}
			m_fAngle = 0.f;
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		{
			m_tInfo.fY -= m_fSpeed;
			m_pFrameKey = L"Player_UP";
			m_fAngle = 270.f;
			m_eCurState = WALK;
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		{
			m_fAngle = 90.f;
			m_tInfo.fY += m_fSpeed;
			m_pFrameKey = L"Player_DOWN";
			m_eCurState = WALK;
		}

		else
		{
			m_eCurState = IDLE;
		}
	}
	else //구르는 중일때
	{
		if (m_eCurState == ROLL)
		{
			m_tInfo.fX += m_fSpeed * 1.5f * (float)cos(m_fAngle * PI / 180.f);
			m_tInfo.fY += m_fSpeed * 1.5f * (float)sin(m_fAngle * PI / 180.f);

		}
		else if (m_eCurState == HIT)
		{
			m_tInfo.fX -= m_fSpeed * 1.5f * (float)cos(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * 1.5f * (float)sin(m_fAngle * PI / 180.f);
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bAction = true;
		m_eCurState = ROLL;
		CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
		CSoundMgr::Get_Instance()->PlaySound(L"Dodge.wav", SOUND_PLAYER, g_fSound);

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('Q') && m_bAction == false)
	{

		if (nullptr != CInventoryMgr::Get_Instance()->Get_ItemSlotQ())
		{
			m_bAction = true;
			m_eCurState = ItemCode_To_State(static_cast<CItem*>(CInventoryMgr::Get_Instance()->Get_ItemSlotQ())->Get_ItemCode());
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"Attack.wav", SOUND_PLAYER, g_fSound);
		}

	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W') && m_bAction == false)
	{
		if (nullptr != CInventoryMgr::Get_Instance()->Get_ItemSlotW())
		{
			m_bAction = true;
			m_eCurState = ItemCode_To_State(static_cast<CItem*>(CInventoryMgr::Get_Instance()->Get_ItemSlotW())->Get_ItemCode());
			CSoundMgr::Get_Instance()->StopSound(SOUND_PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"Attack.wav", SOUND_PLAYER, g_fSound);
		}
	}


}



void CPlayer::OffSet()
{
	int	iOffSetMinX = 100;
	int	iOffSetMaxX = 700;

	int	iOffSetMinY = 100;
	int	iOffSetMaxY = 500;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 2;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 30;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();

			break;

		case ROLL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			Set_Invincibility();

			break;

		case DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case SWORD_STATE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			Use_Item(SWORD);

			break;
		case BOOMERANG_STATE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 8;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			Use_Item(BOOMERANG);
			break;

		case SHIELD_STATE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.iMotion = 7;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			Use_Item(SHIELD);
			break;
		case WAND_STATE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iMotion = 9;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			Use_Item(WAND);
			break;

		case GET_ITEM:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 11;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			break;
		case STATE_END:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}

}
void CPlayer::OffSet2()
{
	int		iOffSetMinX = 350;
	int		iOffSetMaxX = 450;

	int		iOffSetMinY = 250;
	int		iOffSetMaxY = 350;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//if (SC_PUZZLE_STAGE == CSceneMgr::Get_Instance()->Get_CurSceneId() &&
	//	(PUZZLE_STAGE_SECTION1_SNAKE_MINX < m_tInfo.fX && PUZZLE_STAGE_SECTION1_SNAKE_MAXX > m_tInfo.fX) &&
	//	(PUZZLE_STAGE_SECTION1_SNAKE_MINY < m_tInfo.fY && PUZZLE_STAGE_SECTION1_SNAKE_MAXY > m_tInfo.fY)) //1구간 스네이크 용
	//{

	//	CScrollMgr::Get_Instance()->Set_ScrollPos(PUZZLE_STAGE_SECTION1_SNAKE_SCROLLX, PUZZLE_STAGE_SECTION1_SNAKE_SCROLLY);
	//	return;
	//}
	//if (SC_PUZZLE_STAGE == CSceneMgr::Get_Instance()->Get_CurSceneId() &&
	//	(PUZZLE_STAGE_SECTION2_SNAKE_MINX < m_tInfo.fX && PUZZLE_STAGE_SECTION2_SNAKE_MAXX > m_tInfo.fX) &&
	//	(PUZZLE_STAGE_SECTION2_SNAKE_MINY < m_tInfo.fY && PUZZLE_STAGE_SECTION2_SNAKE_MAXY > m_tInfo.fY)) //2구간 스네이크 용
	//{
	//	CScrollMgr::Get_Instance()->Set_ScrollPos(PUZZLE_STAGE_SECTION2_SNAKE_SCROLLX, PUZZLE_STAGE_SECTION2_SNAKE_SCROLLY);
	//	return;
	//}

	if (iOffSetMinX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetMinX - (m_tInfo.fX + iScrollX));

	if (iOffSetMaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetMaxX - (m_tInfo.fX + iScrollX));

	if (iOffSetMinY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetMinY - (m_tInfo.fY + iScrollY));

	if (iOffSetMaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetMaxY - (m_tInfo.fY + iScrollY));
}
void CPlayer::Use_Item(ITEMCODE _eItemCode)
{
	DWORD dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
	switch (_eItemCode)
	{
	case SWORD:
		//소드총알 만들어주기.
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, Create_Bullet<CSwordBullet>(m_tInfo.fX, m_tInfo.fY, m_fAngle, dwMotionTime));
		break;
	case WAND:
		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER_BULLET, Create_Bullet<CWandBullet>(m_tInfo.fX, m_tInfo.fY, m_fAngle, dwMotionTime + (DWORD)BULLET_RENDER_TIME));
		break;
	case SHIELD:
		CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD, Create_Bullet<CShieldBullet>(m_tInfo.fX, m_tInfo.fY, m_fAngle, dwMotionTime));
		break;
	case BOOMERANG:
		if (0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_BOOMERANG_BULLET).size())
			CObjMgr::Get_Instance()->Add_Object(OBJ_BOOMERANG_BULLET, Create_Bullet<CBoomerangBullet>(m_tInfo.fX, m_tInfo.fY, m_fAngle, dwMotionTime));
		break;
	case ITEMCODE_END:
		break;
	default:
		break;
	}

}

STATE CPlayer::ItemCode_To_State(ITEMCODE _eId)
{
	STATE Result = STATE_END;
	switch (_eId)
	{
	case SWORD:
		Result = SWORD_STATE;
		break;
	case WAND:
		Result = WAND_STATE;
		break;
	case SHIELD:
		Result = SHIELD_STATE;
		break;
	case BOOMERANG:
		Result = BOOMERANG_STATE;
		break;
	case ITEMCODE_END:
		break;
	default:
		break;
	}

	return Result;
}
CObj* CPlayer::Create_Shield()
{
	CObj* pObj = CAbstractFactory<CShield>::Create();
	pObj->Set_Target(this);

	return pObj;
}


