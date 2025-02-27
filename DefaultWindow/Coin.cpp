#include "stdafx.h"
#include "Coin.h"
#include "BmpMgr.h"

void CCoin::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/�ո�.bmp", L"�ո�");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/�޸�.bmp", L"�޸�");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RSP/QuestionMark.bmp", L"QuestionMark");

    m_COINID = FRONT;
    m_pFrameKey = L"�ո�";

    m_tInfo.fCX = RSP_IMAGE_CX;
    m_tInfo.fCY = RSP_IMAGE_CY;
}

int CCoin::Update()
{
    __super::Update_Rect();
    return 0;
}

void CCoin::Late_Update()
{
}

void CCoin::Render(HDC hDC)
{
    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    //BitBlt(hDC, (int)m_tRect.left, (int)m_tRect.top, RSP_IMAGE_CX, RSP_IMAGE_CY, hMemDC, 0, 0, SRCCOPY);

    GdiTransparentBlt(hDC,
        (int)m_tRect.left, // ���� ���� ��ġ x, y ��ǥ
        (int)m_tRect.top,
        RSP_IMAGE_CX,	// ���� ���� ����, ���� ����
        RSP_IMAGE_CY,
        hMemDC,		// ������ �̹��� dc
        0,
        0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        RSP_IMAGE_CX,	// ������ �̹����� ����, ���� ������
        RSP_IMAGE_CY,
        RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
}

void CCoin::Release()
{
}
