#include "stdafx.h"
#include "BossExplosionEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CBossExplosionEffect::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/BossExplosion.bmp", L"BossExplosion");
    m_pFrameKey = L"BossExplosion";

    m_tInfo.fCX = BOSS_EXPLOSION_EFFECT_RANGECX;
    m_tInfo.fCY = BOSS_EXPLOSION_EFFECT_RANGECY;
    m_fSpeed = 0.f;
    m_eRender = RENDER_EFFECT;

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 10;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 50;
    m_tFrame.dwMotionTime = DWORD((m_tFrame.iFrameEnd - m_tFrame.iFrameStart + 1) * m_tFrame.dwSpeed) + GetTickCount();
}

int CBossExplosionEffect::Update()
{
    if (m_bDead)
        return OBJ_DEAD;

    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CBossExplosionEffect::Late_Update()
{
    if (m_tFrame.dwMotionTime < GetTickCount())
        m_bDead = true;

    __super::Move_Frame();
}

void CBossExplosionEffect::Render(HDC hDC)
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
        RGB(0, 19, 127));	// �����ϰ��� �ϴ� ����
}

void CBossExplosionEffect::Release()
{
}
