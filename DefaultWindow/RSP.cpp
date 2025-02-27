#include "stdafx.h"
#include "RSP.h"
#include "BmpMgr.h"

void CRSP::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RSP/Rock.bmp", L"Rock");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RSP/Scissors.bmp", L"Scissors");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RSP/Paper.bmp", L"Paper");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/RSP/QuestionMark.bmp", L"QuestionMark");
    
    m_RSPID = ROCK;
    m_pFrameKey = L"Rock";

    m_tInfo.fCX = RSP_IMAGE_CX;
    m_tInfo.fCY = RSP_IMAGE_CY;
}

int CRSP::Update()
{
    __super::Update_Rect();
    return 0;
}

void CRSP::Late_Update()
{
}

void CRSP::Render(HDC hDC)
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

void CRSP::Release()
{
}
