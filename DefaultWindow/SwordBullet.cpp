#include "stdafx.h"
#include "SwordBullet.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "SwordEffect.h"
//#include "SwordEffect.h"

void CSwordBullet::Initialize()
{
    m_tInfo.fCX = SWORD_BULLET_RANGECX;
    m_tInfo.fCY = SWORD_BULLET_RANGECY;
    m_fSpeed = 0.f;
    m_eRender = RENDER_GAMEOBJECT;


}

int CSwordBullet::Update()
{
    if (m_bDead)
    {
        if (true == m_bInvincibility)
        {
            float fX(m_tInfo.fX), fY(m_tInfo.fY);
            if (0.f == m_fAngle) //오른쪽
            {
                fX = m_tInfo.fX + SWORD_BULLET_RANGECY * 0.5f;
            }
            else if (90.f == m_fAngle) //아래쪽
            {
                fY = m_tInfo.fY + SWORD_BULLET_RANGECY * 0.5f;
            }
            else if (180.f == m_fAngle) //왼쪽
            {
                fX = m_tInfo.fX - SWORD_BULLET_RANGECY * 0.5f;
            }
            else if (270.f == m_fAngle) //위쪽
            {
                fY = m_tInfo.fY - SWORD_BULLET_RANGECY * 0.5f;
            }
            CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CObjMgr::Get_Instance()->Create_Effect<CSwordEffect>(fX, fY));
        }
        return OBJ_DEAD;
    }

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CSwordBullet::Late_Update()
{
    if (m_tFrame.dwMotionTime < GetTickCount())
        m_bDead = true;
}

void CSwordBullet::Render(HDC hDC)
{
     /*int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
     int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

     Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);*/

}

void CSwordBullet::Release()
{
}

void CSwordBullet::Set_Pos(float _fX, float _fY)
{
    if (0.f == m_fAngle) //오른쪽
    {
        m_tInfo.fCX = SWORD_BULLET_RANGECY;
        m_tInfo.fCY = SWORD_BULLET_RANGECX;
        m_tInfo.fX = _fX + 60.f * 0.5f;
        m_tInfo.fY = _fY;
    }
    else if (90.f == m_fAngle) //아래쪽
    {
        m_tInfo.fCX = SWORD_BULLET_RANGECX;
        m_tInfo.fCY = SWORD_BULLET_RANGECY;
        m_tInfo.fX = _fX;
        m_tInfo.fY = _fY + 60.f * 0.5f;
    }
    else if (180.f == m_fAngle) //왼쪽
    {
        m_tInfo.fCX = SWORD_BULLET_RANGECY;
        m_tInfo.fCY = SWORD_BULLET_RANGECX;
        m_tInfo.fX = _fX - 60.f * 0.5f;
        m_tInfo.fY = _fY;
    }
    else if (270.f == m_fAngle) //위쪽
    {
        m_tInfo.fCX = SWORD_BULLET_RANGECX;
        m_tInfo.fCY = SWORD_BULLET_RANGECY;
        m_tInfo.fX = _fX;
        m_tInfo.fY = _fY - 60.f * 0.5f;
    }


}
