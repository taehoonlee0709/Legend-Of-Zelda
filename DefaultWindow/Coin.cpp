#include "stdafx.h"
#include "Coin.h"
#include "BmpMgr.h"

void CCoin::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/앞면.bmp", L"앞면");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin/뒷면.bmp", L"뒷면");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RSP/QuestionMark.bmp", L"QuestionMark");

    m_COINID = FRONT;
    m_pFrameKey = L"앞면";

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
        (int)m_tRect.left, // 복사 받을 위치 x, y 좌표
        (int)m_tRect.top,
        RSP_IMAGE_CX,	// 복사 받을 가로, 세로 길이
        RSP_IMAGE_CY,
        hMemDC,		// 복사할 이미지 dc
        0,
        0,		// 비트맵 이미지 출력 시작 좌표
        RSP_IMAGE_CX,	// 복사할 이미지의 가로, 세로 사이즈
        RSP_IMAGE_CY,
        RGB(255, 255, 255));	// 제거하고자 하는 색상값
}

void CCoin::Release()
{
}
