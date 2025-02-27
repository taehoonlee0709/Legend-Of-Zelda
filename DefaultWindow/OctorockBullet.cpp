#include "stdafx.h"
#include "OctorockBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void COctorockBullet::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/OctorockBullet.bmp", L"OctorockBullet");
    m_pFrameKey = L"OctorockBullet";
    m_tInfo.fCX = OCTOROCK_BULLET_COLLISIONCX;
    m_tInfo.fCY = OCTOROCK_BULLET_COLLISIONCY;
    //m_tInfo.fCX = 100.f;
    //m_tInfo.fCY = 100.f;
    m_fSpeed = 5.f;
    m_eRender = RENDER_GAMEOBJECT;
    m_fAngle = 180.f;

    //m_dwDelayTime = GetTickCount() + (DWORD)OCTOROK_BULLET_DELAY;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 2;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 50;
    m_tFrame.dwMotionTime = OCTOROCK_BULLET_LIFETIME + GetTickCount();
}

int COctorockBullet::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
    m_tInfo.fY += m_fSpeed * (float)sin(m_fAngle * PI / 180.f);

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void COctorockBullet::Late_Update()
{
    if (GetTickCount() > m_tFrame.dwMotionTime)
        m_bDead = true;
}

void COctorockBullet::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - (float)OCTOROCK_BULLET_IMAGE_CX * 0.5f) + iScrollX, // ���� ���� ��ġ x, y ��ǥ
        int(m_tInfo.fY - (float)OCTOROCK_BULLET_IMAGE_CY * 0.5f) + iScrollY,
        OCTOROCK_BULLET_IMAGE_CX,	// ���� ���� ����, ���� ����
        OCTOROCK_BULLET_IMAGE_CY,
        hMemDC,		// ������ �̹��� dc
        OCTOROCK_BULLET_IMAGE_CX * m_tFrame.iFrameStart,
        OCTOROCK_BULLET_IMAGE_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        OCTOROCK_BULLET_IMAGE_CX,	// ������ �̹����� ����, ���� ������
        OCTOROCK_BULLET_IMAGE_CY,
        RGB(255, 0, 255));	// �����ϰ��� �ϴ� ����
}

void COctorockBullet::Release()
{
}
