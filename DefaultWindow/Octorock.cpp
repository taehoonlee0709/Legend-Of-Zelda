#include "stdafx.h"
#include "Octorock.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "OctorockBullet.h"

void COctorock::Initialize()
{
    m_tInfo.fCX = OCTOROCK_COLLISION_CX;
    m_tInfo.fCY = OCTOROCK_COLLISION_CY;

    m_iHp = 1;

    m_fSpeed = 0.f;
    m_fAngle = 90.f;
    m_bInvincibility = false;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 200;
    m_dwShoot_Delay = GetTickCount();
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Octorock.bmp", L"Octorock");
    m_pFrameKey = L"Octorock";

    m_eRender = RENDER_GAMEOBJECT;
}

int COctorock::Update()
{
    if (m_bDead)
        return OBJ_DEAD;
    if (m_bInvincibility)// ���� ����. ������ �׳� ���� �����̸� �ٽ� �ǵ���.
        Set_Invincibility();
    if (m_dwBulletCoolTime + OCTOROCK_BULLET_DELAY < GetTickCount())
    {
        m_dwBulletCoolTime = GetTickCount();

        if (m_dwShoot_Delay + 500 < GetTickCount())
        {
            CObjMgr::Get_Instance()->Add_Object(OBJ_OCTOROK_BULLET, CAbstractFactory<COctorockBullet>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle));
            m_dwShoot_Delay = GetTickCount();
        }
        //�Ҹ� ����. �ޱ� ��������'
    }

    __super::Update_Rect();
    return 0;
}

void COctorock::Late_Update()
{
    if (0 >= m_iHp)
        m_bDead = true;

    Set_Motion();

    __super::Move_Frame();
}

void COctorock::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - OCTOROCK_IMAGE_CX * 0.5f) + iScrollX, // ���� ���� ��ġ x, y ��ǥ
        int(m_tInfo.fY - OCTOROCK_IMAGE_CY * 0.5f) + iScrollY,
        OCTOROCK_IMAGE_CX,	// ���� ���� ����, ���� ����
        OCTOROCK_IMAGE_CY,
        hMemDC,		// ������ �̹��� dc
        OCTOROCK_IMAGE_CX * m_tFrame.iFrameStart,
        OCTOROCK_IMAGE_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        OCTOROCK_IMAGE_CX,	// ������ �̹����� ����, ���� ������
        OCTOROCK_IMAGE_CY,
        RGB(255, 0, 255));	// �����ϰ��� �ϴ� ����
}

void COctorock::Release()
{
}

void COctorock::Set_Motion()
{
    if (0.f == m_fAngle)
        m_tFrame.iMotion = 2;
    else if (90.f == m_fAngle)
        m_tFrame.iMotion = 0;
    else if (180.f == m_fAngle)
        m_tFrame.iMotion = 1;
    else if (270.f == m_fAngle)
        m_tFrame.iMotion = 3;
}
