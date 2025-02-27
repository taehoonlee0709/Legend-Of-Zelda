#include "stdafx.h"
#include "FireBallBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"


void CFireBallBullet::Initialize()
{
	m_tInfo.fCX = FIREBALL_BULLET_COLLISIONCX;
	m_tInfo.fCY = FIREBALL_BULLET_COLLISIONCX;

	m_fSpeed = 5.f;
	//m_fDistance = 100.f;
	//m_fAngle = 90.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossGuhu/FireBallBullet.bmp", L"FireBallBullet");

	m_pFrameKey = L"FireBallBullet";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
	m_tFrame.dwSpeed = 50;

	m_eRender = RENDER_GAMEOBJECT;
}

int CFireBallBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	//if (m_dwDelayTime > GetTickCount())
	//	return OBJ_NOEVENT;
	m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
	m_tInfo.fY += m_fSpeed * (float)sin(m_fAngle * PI / 180.f);


	Update_Rect();
	return OBJ_NOEVENT;
}

void CFireBallBullet::Late_Update()
{


	if (m_tFrame.dwMotionTime < GetTickCount()) //�ð� ������ �����.
		m_bDead = true;

	__super::Move_Frame();
}

void CFireBallBullet::Render(HDC hDC)
{

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
		m_tRect.top + iScrollY,
		FIREBALL_BULLET_IMAGE_CX,	// ���� ���� ����, ���� ����
		FIREBALL_BULLET_IMAGE_CY,
		hMemDC,		// ������ �̹��� dc
		FIREBALL_BULLET_IMAGE_CX * m_tFrame.iFrameStart,
		FIREBALL_BULLET_IMAGE_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		FIREBALL_BULLET_IMAGE_CX,	// ������ �̹����� ����, ���� ������
		FIREBALL_BULLET_IMAGE_CY,
		RGB(128, 128, 128));	// �����ϰ��� �ϴ� ����


	//Ellipse(hDC,);
}

void CFireBallBullet::Release()
{
}
