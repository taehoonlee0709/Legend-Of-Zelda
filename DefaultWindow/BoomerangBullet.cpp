#include "stdafx.h"
#include "BoomerangBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

void CBoomerangBullet::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BoomerangBullet.bmp", L"BoomerangBullet");
    m_pFrameKey = L"BoomerangBullet";
    m_tInfo.fCX = BOOMERANG_BULLET_COLLISIONCX;
    m_tInfo.fCY = BOOMERANG_BULLET_COLLISIONCY;
    m_fSpeed = 5.f;
    m_eRender = RENDER_GAMEOBJECT;

    m_dwDelayTime = GetTickCount() + (DWORD)BOOMERANG_BULLET_DELAY;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 50;

    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"MC_Boomerang.wav", SOUND_EFFECT, 1.f);
}

int CBoomerangBullet::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    if (m_dwDelayTime > GetTickCount())
        return OBJ_NOEVENT;


    m_fSpeed -= 0.1f;

    m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
    m_tInfo.fY += m_fSpeed * (float)sin(m_fAngle * PI / 180.f);


    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CBoomerangBullet::Late_Update()
{
    if (10.f <= abs(m_fSpeed))
        m_bDead = true;
    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size() && 0 > m_fSpeed)
    {
        RECT rc{};
        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &this->Get_Rect()))
        {
            m_bDead = true;
        }

    }
    __super::Move_Frame();
}

void CBoomerangBullet::Render(HDC hDC)
{
    if (m_dwDelayTime > GetTickCount())
        return;


    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
        m_tRect.top + iScrollY,
        BOOMERANG_BULLET_IMAGE_CX,	// ���� ���� ����, ���� ����
        BOOMERANG_BULLET_IMAGE_CY,
        hMemDC,		// ������ �̹��� dc
        BOOMERANG_BULLET_IMAGE_CX * m_tFrame.iFrameStart,
        BOOMERANG_BULLET_IMAGE_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        BOOMERANG_BULLET_IMAGE_CX,	// ������ �̹����� ����, ���� ������
        BOOMERANG_BULLET_IMAGE_CY,
        RGB(192, 192, 255));	// �����ϰ��� �ϴ� ����
}

void CBoomerangBullet::Release()
{
}

void CBoomerangBullet::Set_Pos(float _fX, float _fY)
{
    if (0.f == m_fAngle) //������
    {

        m_tInfo.fX = _fX + 60.f * 0.5f;
        m_tInfo.fY = _fY;
    }
    else if (90.f == m_fAngle) //�Ʒ���
    {

        m_tInfo.fX = _fX;
        m_tInfo.fY = _fY + 60.f * 0.5f;
    }
    else if (180.f == m_fAngle) //����
    {

        m_tInfo.fX = _fX - 60.f * 0.5f;
        m_tInfo.fY = _fY;
    }
    else if (270.f == m_fAngle) //����
    {

        m_tInfo.fX = _fX;
        m_tInfo.fY = _fY - 60.f * 0.5f;
    }
}
