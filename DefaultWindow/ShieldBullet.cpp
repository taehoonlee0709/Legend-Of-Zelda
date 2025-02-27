#include "stdafx.h"
#include "ShieldBullet.h"
#include "ScrollMgr.h"

void CShieldBullet::Initialize()
{
    m_tInfo.fCX = SHIELD_BULLET_RANGECX;
    m_tInfo.fCY = SHIELD_BULLET_RANGECY;
    m_fSpeed = 0.f;
    m_eRender = RENDER_GAMEOBJECT;
}

int CShieldBullet::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CShieldBullet::Late_Update()
{
    if (m_tFrame.dwMotionTime < GetTickCount())
        m_bDead = true;
}

void CShieldBullet::Render(HDC hDC)
{
    /*int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);*/
}

void CShieldBullet::Release()
{
}

void CShieldBullet::Set_Pos(float _fX, float _fY)
{
    if (0.f == m_fAngle) //오른쪽
    {
        m_tInfo.fCX = SHIELD_BULLET_RANGECY;
        m_tInfo.fCY = SHIELD_BULLET_RANGECX;
        m_tInfo.fX = _fX + 60.f * 0.5f;
        m_tInfo.fY = _fY;
    }
    else if (90.f == m_fAngle) //아래쪽
    {
        m_tInfo.fCX = SHIELD_BULLET_RANGECX;
        m_tInfo.fCY = SHIELD_BULLET_RANGECY;
        m_tInfo.fX = _fX;
        m_tInfo.fY = _fY + 60.f * 0.5f;
    }
    else if (180.f == m_fAngle) //왼쪽
    {
        m_tInfo.fCX = SHIELD_BULLET_RANGECY;
        m_tInfo.fCY = SHIELD_BULLET_RANGECX;
        m_tInfo.fX = _fX - 60.f * 0.5f;
        m_tInfo.fY = _fY;
    }
    else if (270.f == m_fAngle) //위쪽
    {
        m_tInfo.fCX = SHIELD_BULLET_RANGECX;
        m_tInfo.fCY = SHIELD_BULLET_RANGECY;
        m_tInfo.fX = _fX;
        m_tInfo.fY = _fY - 60.f * 0.5f;
    }
}
