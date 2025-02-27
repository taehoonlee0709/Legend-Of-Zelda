#include "stdafx.h"
#include "RSPMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"


CRSPMgr* CRSPMgr::m_pInstance = nullptr;


void CRSPMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/BG_Inven.bmp", L"BG_Inven");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/cursor.bmp", L"RSPCursor");

    //m_bIsRSPOpen = true;

	m_vecPlayerRSP.push_back(Create_RSP(PLAYER_ROCK_POSX, PLAYER_ROCK_POSY, L"Rock", ROCK));
	m_vecPlayerRSP.push_back(Create_RSP(PLAYER_SCISSORS_POSX, PLAYER_SCISSORS_POSY, L"Scissors", SCISSORS));
	m_vecPlayerRSP.push_back(Create_RSP(PLAYER_PAPER_POSX, PLAYER_PAPER_POSY, L"Paper", PAPER));

	m_AIRSP = Create_RSP(PLAYER_SCISSORS_POSX, PLAYER_PAPER_POSY - 300, L"QuestionMark", QUESTION_MARK);
}

int CRSPMgr::Update()
{
    if (false == m_bIsRSPOpen)
        return 0 ;

	Key_Input();
    for (auto& iter : m_vecPlayerRSP)
    {
        iter->Update();
    }

	return 0;
}

void CRSPMgr::Late_Update()
{
}

void CRSPMgr::Render(HDC hDC)
{
    if (false == m_bIsRSPOpen)
        return;

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BG_Inven");
    HDC	hAIDC = CBmpMgr::Get_Instance()->Find_Image(m_AIRSP->Get_FrameKey());
    HDC	hCursorDC = CBmpMgr::Get_Instance()->Find_Image(L"RSPCursor");
    //백그라운드 출력
    BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

    //플레이어 손 출력
    for (auto& iter : m_vecPlayerRSP)
    {
        iter->Render(hDC);
    }


    //커서 출력

    int iStart = int((GetTickCount() % 1000) / 500);

    GdiTransparentBlt(hDC,
        int(m_vecPlayerRSP[m_iCursor]->Get_Info().fX - 0.5f * RSP_CURSOR_CX), // 복사 받을 위치 x, y 좌표
        int(m_vecPlayerRSP[m_iCursor]->Get_Info().fY - 0.5f * RSP_CURSOR_CY),
        RSP_CURSOR_CX,	// 복사 받을 가로, 세로 길이
        RSP_CURSOR_CY,
        hCursorDC,		// 복사할 이미지 dc
        iStart * RSP_CURSOR_CX,
        0,		// 비트맵 이미지 출력 시작 좌표
        RSP_CURSOR_CX,	// 복사할 이미지의 가로, 세로 사이즈
        RSP_CURSOR_CY,
        RGB(255, 255, 255));	// 제거하고자 하는 색상값.

    //적 손 출력
    GdiTransparentBlt(hDC,
        int(m_AIRSP->Get_Info().fX - 0.5f * m_AIRSP->Get_Info().fCX), // 복사 받을 위치 x, y 좌표
        int(m_AIRSP->Get_Info().fY - 0.5f * m_AIRSP->Get_Info().fCY),
        int(m_AIRSP->Get_Info().fCX),	// 복사 받을 가로, 세로 길이
        int(m_AIRSP->Get_Info().fCY),
        hAIDC,		// 복사할 이미지 dc
        0,
        0,		// 비트맵 이미지 출력 시작 좌표
        int(m_AIRSP->Get_Info().fCX),	// 복사할 이미지의 가로, 세로 사이즈
        int(m_AIRSP->Get_Info().fCY),
        RGB(255, 255, 255));	// 제거하고자 하는 색상값

    if (m_bIsEnter)
    {
        HFONT hFont, OldFont;
        hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"바탕");
        OldFont = (HFONT)SelectObject(hDC, hFont);
        SetTextColor(hDC, RGB(0, 0, 0));
        SetBkMode(hDC, TRANSPARENT);

        RECT rcResult = { 0,LONG(WINCY * 0.45f),WINCX,WINCY };
        DrawText(hDC, m_szResult, lstrlen(m_szResult), &rcResult, DT_CENTER | DT_WORDBREAK);

        SelectObject(hDC, OldFont);

        DeleteObject(hFont);

    }

}

void CRSPMgr::Release()
{
	for_each(m_vecPlayerRSP.begin(), m_vecPlayerRSP.end(), CDeleteObj());
	m_vecPlayerRSP.clear();
	Safe_Delete(m_AIRSP);
}

void CRSPMgr::Key_Input()
{


    if (true == m_bIsRSPOpen)
    {

        if (CKeyMgr::Get_Instance()->Key_Down(VK_LEFT) && false == m_bIsEnter)
        {
            if (0 == m_iCursor)
                return;
            --m_iCursor;
        }
        else if (CKeyMgr::Get_Instance()->Key_Down(VK_RIGHT) && false == m_bIsEnter)
        {
            if (2 == m_iCursor)
                return;
            ++m_iCursor;
        }
        else if (CKeyMgr::Get_Instance()->Key_Down('B'))
        {
            Check_RSP();
           // Select_RSP();
        }
        else if (CKeyMgr::Get_Instance()->Key_Down('V'))
        {
            if(Get_IsRSPOpen() && true == m_bIsEnter)
            {
                Set_IsRSPOpen();
                m_bIsEnter = false;
                m_vecPlayerRSP[m_iCursor]->Set_PosY(50.f);
                m_AIRSP->Set_FrameKey(L"QuestionMark");
                static_cast<CRSP*>(m_AIRSP)->Set_RSP_ID(QUESTION_MARK);
            }
        }
    }
}

void CRSPMgr::Check_RSP()
{
    
    if (false != m_bIsEnter)
        return;

    m_AIRSP->Set_FrameKey(L"Rock");
    static_cast<CRSP*>(m_AIRSP)->Set_RSP_ID(ROCK);
    m_vecPlayerRSP[m_iCursor]->Set_PosY(-50.f);

    if (m_iCursor == 0)//주먹
    {
        m_szResult = L"무승부";
    }
    else if (m_iCursor == 1)//가위
    {
        m_szResult = L"졌다ㅠ";
        
    }
    else if (m_iCursor == 2)//보
    {
        m_szResult = L"이겼다!";
        if (!Get_IsPlayerWin())
        {
            Set_IsPlayerWin();
        }
        CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
    }
    m_bIsEnter = true;
}


CObj* CRSPMgr::Create_RSP(float _fX, float _fY, TCHAR* _szFrameKey, RSPID _eID)
{
	CObj* pObj = new CRSP;
	pObj->Initialize();
	pObj->Set_Pos(_fX, _fY);
	pObj->Set_FrameKey(_szFrameKey);
	static_cast<CRSP*>(pObj)->Set_RSP_ID(_eID);


	return pObj;
}
