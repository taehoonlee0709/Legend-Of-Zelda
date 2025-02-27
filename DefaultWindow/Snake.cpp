#include "stdafx.h"
#include "Snake.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CSnake::Initialize()
{
    m_tInfo.fCX = SNAKE_COLLISION_CX;
    m_tInfo.fCY = SNAKE_COLLISION_CY;

    m_iHp = 1;

    m_fSpeed = 1.f;
    m_fAngle = 90.f;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 2;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 100;

    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Snake.bmp", L"Snake");
    m_pFrameKey = L"Snake";

    m_eRender = RENDER_GAMEOBJECT;

    m_PatternQueue.push(SNAKE_DOWN);
    m_PatternQueue.push(SNAKE_LEFT);
    m_PatternQueue.push(SNAKE_UP);
    m_PatternQueue.push(SNAKE_RIGHT);

}

int CSnake::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.fX += m_fSpeed * (float)cos(m_fAngle * PI / 180.f);
    m_tInfo.fY += m_fSpeed * (float)sin(m_fAngle * PI / 180.f);

    Pattern_Change();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CSnake::Late_Update()
{
    if (0 >= m_iHp)
    {
        m_eCurPattern = SNAKE_DEAD;

    }
    if (SNAKE_DEAD == m_eCurPattern && GetTickCount() > m_tFrame.dwMotionTime)
        m_bDead = true;

    __super::Move_Frame();

    Motion_Change();
}

void CSnake::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - SNAKE_IMAGE_CX * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
        int(m_tInfo.fY - SNAKE_IMAGE_CY * 0.5f) + iScrollY,
        SNAKE_IMAGE_CX,	// 복사 받을 가로, 세로 길이
        SNAKE_IMAGE_CY,
        hMemDC,		// 복사할 이미지 dc
        SNAKE_IMAGE_CX * m_tFrame.iFrameStart,
        SNAKE_IMAGE_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
        SNAKE_IMAGE_CX,	// 복사할 이미지의 가로, 세로 사이즈
        SNAKE_IMAGE_CY,
        RGB(0, 0, 0));	// 제거하고자 하는 색상값
}

void CSnake::Release()
{
}

void CSnake::Motion_Change()
{
    if (m_ePrePattern != m_eCurPattern)
    {
        switch (m_eCurPattern)
        {
        case SNAKE_LEFT:
            m_fAngle = 180.f;
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 0;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwMotionTime = SNAKE_WALK_TIME + GetTickCount();
            m_PatternQueue.push(SNAKE_LEFT);
            break;
        case SNAKE_RIGHT:
            m_fAngle = 0.f;
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 1;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwMotionTime = SNAKE_WALK_TIME + GetTickCount();
            m_PatternQueue.push(SNAKE_RIGHT);
            break;
        case SNAKE_DOWN:
            m_fAngle = 90.f;
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 2;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwMotionTime = SNAKE_WALK_TIME + GetTickCount();
            m_PatternQueue.push(SNAKE_DOWN);
            break;
        case SNAKE_UP:
            m_fAngle = 270.f;
            m_tFrame.iFrameStart = 0;
            m_tFrame.iFrameEnd = 3;
            m_tFrame.iMotion = 3;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.dwSpeed = 200;
            m_tFrame.dwMotionTime = SNAKE_WALK_TIME + GetTickCount();
            m_PatternQueue.push(SNAKE_UP);
            break;
        case SNAKE_DEAD:
            m_fSpeed = 0.f;
            m_tFrame.iFrameStart = 4;
            m_tFrame.iFrameEnd = 12;
            m_tFrame.iMotion = 4;
            m_tFrame.dwTime = GetTickCount();
            m_tFrame.dwSpeed = 50;
            m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
            break;
        case SNAKE_PATTERN_END:
            break;
        default:
            break;
        }

        m_ePrePattern = m_eCurPattern;
    }

}

void CSnake::Pattern_Change()
{
    if (GetTickCount() > m_tFrame.dwMotionTime)
    {
        if (0 < m_PatternQueue.size())
        {
            m_eCurPattern = m_PatternQueue.front();
            m_PatternQueue.pop();
        }
        else
            m_eCurPattern = SNAKE_DOWN;
    }
}

