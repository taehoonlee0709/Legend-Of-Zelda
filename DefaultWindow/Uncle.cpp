#include "stdafx.h"
#include "Uncle.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "TextBoxMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "CoinMgr.h"
#include "SoundMgr.h"
//#include "SlidePuzzleMgr.h"

void CUncle::Initialize()
{
    m_tInfo.fCX = NPC_SLIDEPUZZLE_CX;
    m_tInfo.fCY = NPC_SLIDEPUZZLE_CY;

    m_eRender = RENDER_GAMEOBJECT;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NpcSlidePuzzle.bmp", L"NpcSlidePuzzle");
    m_pFrameKey = L"NpcSlidePuzzle";
}

int CUncle::Update()
{
    m_eCurState = NPC_SLIDEPUZZLE_IDLE;
    Key_Input();
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CUncle::Late_Update()
{
    CollisionPlayer();
    State_Change();
    //m_bIsItemGived = CSlidePuzzleMgr::Get_Instance()->Get_IsPuzzleSolved();
    //if (false == m_bInvincibility)
    //{
    //    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
    //    {
    //        RECT rc{};
    //        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &this->Get_Rect()))
    //        {
    //            //MessageBox(g_hWnd, _T("어딜만져"), _T("물건파는 아저씨"), MB_OK);
    //            CTextBoxMgr::Get_Instance()->Set_Text(L"보스를 잡아주시게. 우리 마을의 희망이여..!");
    //            if(false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
    //                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
    //            CollisionPlayer();

    //        }

    //    }
    //}
}

void CUncle::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - NPC_SLIDEPUZZLE_CX * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
        int(m_tInfo.fY - NPC_SLIDEPUZZLE_CY * 0.5f) + iScrollY,
        (int)NPC_SLIDEPUZZLE_CX,	// 복사 받을 가로, 세로 길이
        (int)NPC_SLIDEPUZZLE_CY,
        hMemDC,		// 복사할 이미지 dc
        (int)NPC_SLIDEPUZZLE_CX * m_tFrame.iFrameStart,
        (int)NPC_SLIDEPUZZLE_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
        (int)NPC_SLIDEPUZZLE_CX,	// 복사할 이미지의 가로, 세로 사이즈
        (int)NPC_SLIDEPUZZLE_CY,
        RGB(171, 0, 0));	// 제거하고자 하는 색상값
}

void CUncle::Release()
{
}

void CUncle::CollisionPlayer()
{
    if (0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
        return;
    CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
    float	fX(0.f), fY(0.f);

    if (CCollisionMgr::Check_Rect(this, pPlayer, &fX, &fY))
    {
        // 상하 충돌
        if (fX > fY)
        {
            // 상 충돌
            if (this->Get_Info().fY < pPlayer->Get_Info().fY)
            {
                pPlayer->Set_PosY(fY);
            }

            else
            {
                pPlayer->Set_PosY(-fY);
            }
        }
        // 좌우 충돌
        else
        {
            // 좌 충돌
            if (this->Get_Info().fX < pPlayer->Get_Info().fX)
            {
                pPlayer->Set_PosX(fX);
            }

            // 우 충돌
            else
            {
                pPlayer->Set_PosX(-fX);
            }
        }

    }
}

void CUncle::Key_Input()
{
    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
    {
        RECT rc{};
        RECT rcThis{ m_tRect.left,m_tRect.top,m_tRect.right, m_tRect.bottom + NPC_SLIDEPUZZLE_INTERACTION_RANGE };
        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &rcThis))
        {
           
            if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
            {
                if (true == m_bIsItemGived)
                    m_eCurState = NPC_SLIDEPUZZLE_AFTER;
                else if (false == m_bIsItemGived && CCoinMgr::Get_Instance()->Get_IsPlayerWin())
                    m_eCurState = NPC_SLIDEPUZZLE_GIVE_ITEM;
                else if (false == m_bIsItemGived && !CCoinMgr::Get_Instance()->Get_IsPlayerWin())
                    m_eCurState = NPC_SLIDEPUZZLE_BEFORE;
               
               
            }

        }

    }
}

void CUncle::State_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case NPC_SLIDEPUZZLE_IDLE:
            break;
        case NPC_SLIDEPUZZLE_BEFORE:
        {
            CTextBoxMgr::Get_Instance()->Set_Text(L"동전 던지기 게임을 해서 이기면 아이템을 주지");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            if (!CCoinMgr::Get_Instance()->Get_IsCoinOpen())
            {
                CCoinMgr::Get_Instance()->Set_IsCoinOpen();

            }
            CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
            CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, 1.f);
        }           
        break;
        case NPC_SLIDEPUZZLE_GIVE_ITEM:
        {
            CTextBoxMgr::Get_Instance()->Set_Text(L"부메랑일세 부메랑은 벽에 충돌하지 않고 공격이 가능하지 하이랄을 잘 부탁하네");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            // CObjMgr::Get_Instance()->Add_Object();
            CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(m_tInfo.fX - 50, m_tInfo.fY, BOOMERANG, L"BoomerangInven"));
            m_bIsItemGived = true;
        }
        break;
        /*case NPC_SLIDEPUZZLE_AFTER:
        {
            CTextBoxMgr::Get_Instance()->Set_Text(L"구후를 무찔러주게. 우리 마을의 희망이여..!");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();

        }
        break;*/
        case NPC_SLIDEPUZZLE_STATE_END:
            break;
        default:
            break;
        }
        m_ePreState = m_eCurState;
    }
}
