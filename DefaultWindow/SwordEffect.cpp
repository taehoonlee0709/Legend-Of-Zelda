#include "stdafx.h"
#include "SwordEffect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

void CSwordEffect::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/SwordEffect.bmp", L"SwordEffect");
    m_pFrameKey = L"SwordEffect";

    m_tInfo.fCX = SWORD_EFFECT_IMAGE_CX;
    m_tInfo.fCY = SWORD_EFFECT_IMAGE_CY;
    m_fSpeed = 0.f;
    m_eRender = RENDER_EFFECT;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 3;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 60;
    m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
}

int CSwordEffect::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CSwordEffect::Late_Update()
{
    if (m_tFrame.dwMotionTime < GetTickCount())
        m_bDead = true;

    __super::Move_Frame();
}

void CSwordEffect::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX, // ���� ���� ��ġ x, y ��ǥ
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
        (int)m_tInfo.fCY,
        hMemDC,		// ������ �̹��� dc
        (int)m_tInfo.fCX * m_tFrame.iFrameStart,
        (int)m_tInfo.fCY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        (int)m_tInfo.fCX,	// ������ �̹����� ����, ���� ������
        (int)m_tInfo.fCY,
        RGB(128, 128, 128));	// �����ϰ��� �ϴ� ����
}

void CSwordEffect::Release()
{
}
