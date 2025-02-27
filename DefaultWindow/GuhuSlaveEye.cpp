#include "stdafx.h"
#include "GuhuSlaveEye.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "RazerBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"

void CGuhuSlaveEye::Initialize()
{
	m_tInfo.fCX = GUHU_SALVE_EYE_COLLISION_CX;
	m_tInfo.fCY = GUHU_SALVE_EYE_COLLISION_CY;

	m_fSpeed = 5.f;
	m_fDistance = 100.f;
	m_fAngle = 90.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossGuhu/BossEyes.bmp", L"BossEyes");

	m_iHp = 2;

	m_pFrameKey = L"BossEyes";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 300;

	m_eRender = RENDER_GAMEOBJECT;

	m_PatternQueue.push(EYE_STATE_IDLE);
	m_PatternQueue.push(EYE_STATE_RAZER);


}

int CGuhuSlaveEye::Update()
{
	if (true == m_bDead && GetTickCount() > m_tFrame.dwMotionTime)
		return OBJ_DEAD;
	//DWORD	dwTime = GetTickCount();
	if (m_bAction == true && GetTickCount() > m_tFrame.dwMotionTime)
	{
		m_bAction = false;
		m_eCurState = EYE_STATE_IDLE;
		m_fAngle = 90.f;

	}



	if (m_bInvincibility)
		Set_Invincibility();

	Pattern_Change();
	//FireBall();

	__super::Update_Rect();
	//Update_Rect();
	return OBJ_NOEVENT;
}

void CGuhuSlaveEye::Late_Update()
{
	if (0 >= m_iHp)
	{
		m_bDead = true;
		m_bAction = true;
		Set_Invincibility();
		m_eCurState = EYE_STATE_DEAD;
	}

	__super::Move_Frame();

	Motion_Change();
}

void CGuhuSlaveEye::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		int(m_tInfo.fX - GUHU_SALVE_EYE_IMAGE_CX * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
		int(m_tInfo.fY - GUHU_SALVE_EYE_IMAGE_CY * 0.5f) + iScrollY,
		(int)GUHU_SALVE_EYE_IMAGE_CX,	// 복사 받을 가로, 세로 길이
		(int)GUHU_SALVE_EYE_IMAGE_CY,
		hMemDC,		// 복사할 이미지 dc
		(int)GUHU_SALVE_EYE_IMAGE_CX * m_tFrame.iFrameStart,
		(int)GUHU_SALVE_EYE_IMAGE_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
		(int)GUHU_SALVE_EYE_IMAGE_CX,	// 복사할 이미지의 가로, 세로 사이즈
		(int)GUHU_SALVE_EYE_IMAGE_CY,
		RGB(255, 255, 255));	// 제거하고자 하는 색상값
}

void CGuhuSlaveEye::Release()
{
}
void CGuhuSlaveEye::Pattern_Change()
{
	if (m_bAction == false)
	{
		m_bAction = true;
		if (0 < m_PatternQueue.size())
		{
			m_eCurState = m_PatternQueue.front();
			m_PatternQueue.pop();

		}
		else
			m_eCurState = EYE_STATE_IDLE;

	}
}
void CGuhuSlaveEye::Motion_Change()
{
	DWORD	dwTime = GetTickCount();
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case EYE_STATE_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 3000;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			break;

		case EYE_STATE_OPEN_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 3;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			break;

		case EYE_STATE_APPEAR:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			break;
		case EYE_STATE_OPEN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iMotion = 2;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;

			break;
		case EYE_STATE_RAZER:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iMotion = 4;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwMotionTime = RAZER_BULLET_RENDER_TIME + GetTickCount();
			CSoundMgr::Get_Instance()->StopSound( SOUND_GUHU_EYE);
			CSoundMgr::Get_Instance()->PlaySound(L"BossRazer.wav", SOUND_GUHU_EYE, 1.f);
			Razer();
			m_PatternQueue.push(EYE_STATE_IDLE);
			m_PatternQueue.push(EYE_STATE_RAZER);
			break;
		case EYE_STATE_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 5;
			m_tFrame.dwTime = GetTickCount();
			m_tFrame.dwSpeed = 50;	
			m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
			break;
		case EYE_STATE_END:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}

}

void CGuhuSlaveEye::Razer()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_BULLET, CAbstractFactory<CRazerBullet>::Create(m_tInfo.fX, m_tInfo.fY + (m_tInfo.fCY + RAZER_BULLET_IMAGE_CY) * 0.5f));
	CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER_BULLET).back()->Set_Target(this);
}
