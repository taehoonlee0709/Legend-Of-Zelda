#include "stdafx.h"
#include "RazerBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CRazerBullet::Initialize()
{
	//m_tInfo.fCX = RAZER_BULLET_COLLISIONCX;
	//m_tInfo.fCY = RAZER_BULLET_COLLISIONCY;

	m_tInfo.fCX = RAZER_BULLET_IMAGE_CX;
	m_tInfo.fCY = RAZER_BULLET_IMAGE_CY;
	m_fSpeed = 0.f;
	//m_fDistance = 100.f;
	//m_fAngle = 90.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossGuhu/RazerBullet.bmp", L"RazerBullet");

	m_pFrameKey = L"RazerBullet";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwMotionTime = GetTickCount() + RAZER_BULLET_RENDER_TIME;
	m_eRender = RENDER_GAMEOBJECT;


}

int CRazerBullet::Update()
{
	if (m_bDead && m_tFrame.dwMotionTime < GetTickCount())
		return OBJ_DEAD;
	if(m_pTarget->Get_Dead())
		return OBJ_DEAD;
	//if (m_dwDelayTime > GetTickCount())
	//	return OBJ_NOEVENT;
	//m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
	//m_tInfo.fY += m_fSpeed * (float)sin(m_fAngle * PI / 180.f);
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY + (m_pTarget->Get_Info().fCY + RAZER_BULLET_IMAGE_CY) * 0.5f;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CRazerBullet::Late_Update()
{
	if (m_tFrame.dwMotionTime < GetTickCount()) //시간 지나면 사라짐.
		m_bDead = true;

	__super::Move_Frame();
}

void CRazerBullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // 복사 받을 위치 x, y 좌표
		m_tRect.top + iScrollY,
		RAZER_BULLET_IMAGE_CX,	// 복사 받을 가로, 세로 길이
		RAZER_BULLET_IMAGE_CY,
		hMemDC,		// 복사할 이미지 dc
		RAZER_BULLET_IMAGE_CX * m_tFrame.iFrameStart,
		RAZER_BULLET_IMAGE_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
		RAZER_BULLET_IMAGE_CX,	// 복사할 이미지의 가로, 세로 사이즈
		RAZER_BULLET_IMAGE_CY,
		RGB(128, 128, 128));	// 제거하고자 하는 색상값

}

void CRazerBullet::Release()
{
}

