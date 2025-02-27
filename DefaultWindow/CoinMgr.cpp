#include "stdafx.h"
#include "CoinMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"


CCoinMgr* CCoinMgr::m_pInstance = nullptr;


void CCoinMgr::Initialize()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/BG_Inven.bmp", L"BG_Inven");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Inventory/cursor.bmp", L"RSPCursor");

    //m_bIsRSPOpen = true;

    m_vecPlayerCoin.push_back(Create_Coin(PLAYER_ROCK_POSX, PLAYER_ROCK_POSY, L"�ո�", FRONT));
    m_vecPlayerCoin.push_back(Create_Coin(PLAYER_PAPER_POSX, PLAYER_PAPER_POSY, L"�޸�", BACK));

    m_AICoin = Create_Coin(PLAYER_SCISSORS_POSX, PLAYER_PAPER_POSY - 300, L"QuestionMark", QUESTION_MARK2);
}

int CCoinMgr::Update()
{
    if (false == m_bIsCoinOpen)
        return 0;

    Key_Input();
    for (auto& iter : m_vecPlayerCoin)
    {
        iter->Update();
    }

    return 0;
}

void CCoinMgr::Late_Update()
{
}

void CCoinMgr::Render(HDC hDC)
{
    if (false == m_bIsCoinOpen)
        return;

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BG_Inven");
    HDC	hAIDC = CBmpMgr::Get_Instance()->Find_Image(m_AICoin->Get_FrameKey());
    HDC	hCursorDC = CBmpMgr::Get_Instance()->Find_Image(L"RSPCursor");
    //��׶��� ���
    BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

    //�÷��̾� �� ���
    for (auto& iter : m_vecPlayerCoin)
    {
        iter->Render(hDC);
    }


    //Ŀ�� ���

    int iStart = int((GetTickCount() % 1000) / 500);

    GdiTransparentBlt(hDC,
        int(m_vecPlayerCoin[m_iCursor]->Get_Info().fX - 0.5f * RSP_CURSOR_CX), // ���� ���� ��ġ x, y ��ǥ
        int(m_vecPlayerCoin[m_iCursor]->Get_Info().fY - 0.5f * RSP_CURSOR_CY),
        RSP_CURSOR_CX,	// ���� ���� ����, ���� ����
        RSP_CURSOR_CY,
        hCursorDC,		// ������ �̹��� dc
        iStart * RSP_CURSOR_CX,
        0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        RSP_CURSOR_CX,	// ������ �̹����� ����, ���� ������
        RSP_CURSOR_CY,
        RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����.

    //�� �� ���
    GdiTransparentBlt(hDC,
        int(m_AICoin->Get_Info().fX - 0.5f * m_AICoin->Get_Info().fCX), // ���� ���� ��ġ x, y ��ǥ
        int(m_AICoin->Get_Info().fY - 0.5f * m_AICoin->Get_Info().fCY),
        int(m_AICoin->Get_Info().fCX),	// ���� ���� ����, ���� ����
        int(m_AICoin->Get_Info().fCY),
        hAIDC,		// ������ �̹��� dc
        0,
        0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        int(m_AICoin->Get_Info().fCX),	// ������ �̹����� ����, ���� ������
        int(m_AICoin->Get_Info().fCY),
        RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����

    if (m_bIsEnter)
    {
        HFONT hFont, OldFont;
        hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"����");
        OldFont = (HFONT)SelectObject(hDC, hFont);
        SetTextColor(hDC, RGB(0, 0, 0));
        SetBkMode(hDC, TRANSPARENT);

        RECT rcResult = { 0,LONG(WINCY * 0.45f),WINCX,WINCY };
        DrawText(hDC, m_szResult, lstrlen(m_szResult), &rcResult, DT_CENTER | DT_WORDBREAK);

        SelectObject(hDC, OldFont);

        DeleteObject(hFont);

    }

}

void CCoinMgr::Release()
{
    for_each(m_vecPlayerCoin.begin(), m_vecPlayerCoin.end(), CDeleteObj());
    m_vecPlayerCoin.clear();
    Safe_Delete(m_AICoin);
}

void CCoinMgr::Key_Input()
{

    if (true == m_bIsCoinOpen)
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
            Check_Coin();
            // Select_RSP();
        }
        else if (CKeyMgr::Get_Instance()->Key_Down('V'))
        {
            if (Get_IsCoinOpen() && true == m_bIsEnter)
            {
                Set_IsCoinOpen();
                m_bIsEnter = false;
                m_vecPlayerCoin[m_iCursor]->Set_PosY(50.f);
                m_AICoin->Set_FrameKey(L"QuestionMark");
                static_cast<CCoin*>(m_AICoin)->Set_COIN_ID(QUESTION_MARK2);
            }
        }
    }
}

void CCoinMgr::Check_Coin()
{
    //int iAIResult = rand() % 3;
    //1,2,3�϶� AI�� �������ֱ�.

    if (false != m_bIsEnter)
        return;

    m_AICoin->Set_FrameKey(L"�ո�");
    static_cast<CCoin*>(m_AICoin)->Set_COIN_ID(FRONT);
    m_vecPlayerCoin[m_iCursor]->Set_PosY(-50.f);

    if (m_iCursor == 0)//�ָ�
    {
        m_szResult = L"�̰��!";
        if (!Get_IsPlayerWin())
        {
            Set_IsPlayerWin();
        }
        CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
        CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
    }
    else if (m_iCursor == 1)//����
    {
        m_szResult = L"���٤�";
    }
    else if (m_iCursor == 2)//��
    {
        m_szResult = L"���٤�";
    }
    m_bIsEnter = true;
}


CObj* CCoinMgr::Create_Coin(float _fX, float _fY, TCHAR* _szFrameKey, COINID _eID)
{
    CObj* pObj = new CCoin;
    pObj->Initialize();
    pObj->Set_Pos(_fX, _fY);
    pObj->Set_FrameKey(_szFrameKey);
    static_cast<CCoin*>(pObj)->Set_COIN_ID(_eID);


    return pObj;
}
