#include "stdafx.h"
#include "Zelda.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TextBoxMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"

void CZelda::Initialize()
{
    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 100.f;

    m_eRender = RENDER_GAMEOBJECT;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NpcZelda.bmp", L"NpcZelda");
    m_pFrameKey = L"NpcZelda";

    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 4;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
    m_tFrame.dwSpeed = 200;
}

int CZelda::Update()
{
    m_eCurState = NPC_ZELDA_IDLE;
    Key_Input();
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CZelda::Late_Update()
{
    CollisionPlayer();
    State_Change();
    //if (false == m_bInvincibility)
    //{
    //    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
    //    {
    //        RECT rc{};
    //        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &this->Get_Rect()))
    //        {
    //            //MessageBox(g_hWnd, _T("어딜만져"), _T("물건파는 아저씨"), MB_OK);
    //            CTextBoxMgr::Get_Instance()->Set_Text(L"링크야, 스네이크 4마리를 잡고, 마을에 가서 보상을 받으려무나.");
    //            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
    //                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
    //            CollisionPlayer();

    //        }

    //    }
    //}

    __super::Move_Frame();
}

void CZelda::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - NPC_ZELDA_CX * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
        int(m_tInfo.fY - NPC_ZELDA_CY * 0.5f) + iScrollY,
        (int)NPC_ZELDA_CX,	// 복사 받을 가로, 세로 길이
        (int)NPC_ZELDA_CY,
        hMemDC,		// 복사할 이미지 dc
        (int)NPC_ZELDA_CX * m_tFrame.iFrameStart,
        (int)NPC_ZELDA_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
        (int)NPC_ZELDA_CX,	// 복사할 이미지의 가로, 세로 사이즈
        (int)NPC_ZELDA_CY,
        RGB(128, 128, 128));	// 제거하고자 하는 색상값
}

void CZelda::Release()
{
}

void CZelda::CollisionPlayer()
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

void CZelda::Key_Input()
{
    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
    {
        RECT rc{};
        RECT rcThis{ m_tRect.left ,m_tRect.top - NPC_ZELDA_INTERACTION_RANGE ,m_tRect.right, m_tRect.bottom + NPC_ZELDA_INTERACTION_RANGE };
        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &rcThis))
        {
            if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
            {

                if (true == m_bIsItemGived)
                    m_eCurState = NPC_ZELDA_AFTER;
                else if (false == m_bIsItemGived)
                    m_eCurState = NPC_ZELDA_GIVE_ITEM;
                /*if (true == m_bIsItemGived)
                    m_eCurState = NPC_SLIDEPUZZLE_AFTER;
                else if (false == m_bIsItemGived && CSlidePuzzleMgr::Get_Instance()->Get_IsPuzzleSolved())
                    m_eCurState = NPC_SLIDEPUZZLE_GIVE_ITEM;
                else if (false == m_bIsItemGived && !CSlidePuzzleMgr::Get_Instance()->Get_IsPuzzleSolved())
                    m_eCurState = NPC_SLIDEPUZZLE_BEFORE;*/
            }

        }

    }
}

void CZelda::State_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case NPC_ZELDA_IDLE:
            break;
        case NPC_ZELDA_BEFORE:
            break;
        case NPC_ZELDA_GIVE_ITEM:
            CTextBoxMgr::Get_Instance()->Set_Text(L"링크 드디어 와줬구나");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            // CObjMgr::Get_Instance()->Add_Object();
           // CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(m_tInfo.fX - 50, m_tInfo.fY, SWORD, L"SwordInven"));
            m_bIsItemGived = true;
            break;
        case NPC_ZELDA_AFTER:
            CTextBoxMgr::Get_Instance()->Set_Text(L"구해줘서 고마워.");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            break;

        case NPC_ZELDA_STATE_END:
            break;
        default:
            break;
        }
        m_ePreState = m_eCurState;
    }
}
