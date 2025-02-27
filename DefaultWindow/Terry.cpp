#include "stdafx.h"
#include "Terry.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TextBoxMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "RSPMgr.h"

void CTerry::Initialize()
{
    m_tInfo.fCX = NPC_QUEST_CX;
    m_tInfo.fCY = NPC_QUEST_CY;

    m_eRender = RENDER_GAMEOBJECT;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NpcQuest.bmp", L"NpcQuest");
    m_pFrameKey = L"NpcQuest";
}

int CTerry::Update()
{
    m_eCurState = NPC_QUEST_IDLE;
    Key_Input();
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CTerry::Late_Update()
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
    //            CTextBoxMgr::Get_Instance()->Set_Text(L"스네이크를 잡아줘요! 해주면 뭔가 줄게요!");
    //            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
    //                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
    //            CollisionPlayer();

    //        }

    //    }
    //}
}

void CTerry::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - NPC_QUEST_CX * 0.5f) + iScrollX, // 복사 받을 위치 x, y 좌표
        int(m_tInfo.fY - NPC_QUEST_CY * 0.5f) + iScrollY,
        (int)NPC_QUEST_CX,	// 복사 받을 가로, 세로 길이
        (int)NPC_QUEST_CY,
        hMemDC,		// 복사할 이미지 dc
        (int)NPC_QUEST_CX * m_tFrame.iFrameStart,
        (int)NPC_QUEST_CY * m_tFrame.iMotion,		// 비트맵 이미지 출력 시작 좌표
        (int)NPC_QUEST_CX,	// 복사할 이미지의 가로, 세로 사이즈
        (int)NPC_QUEST_CY,
        RGB(255, 255, 255));	// 제거하고자 하는 색상값
}

void CTerry::Release()
{
}

void CTerry::CollisionPlayer()
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

void CTerry::Key_Input()
{
    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
    {
        RECT rc{};
        RECT rcThis{ m_tRect.left,m_tRect.top,m_tRect.right, m_tRect.bottom + NPC_QUEST_INTERACTION_RANGE };
        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &rcThis))
        {
            if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
            {
                // m_eCurState = NPC_QUEST_GIVE_ITEM;
                if (true == m_bIsItemGived)
                    m_eCurState = NPC_QUEST_AFTER;
                else if (false == m_bIsItemGived)
                    m_eCurState = NPC_QUEST_GIVE_ITEM;
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

void CTerry::State_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case NPC_QUEST_IDLE:
            break;
        case NPC_QUEST_BEFORE:
        
        break;        
        case NPC_QUEST_GIVE_ITEM:
            CTextBoxMgr::Get_Instance()->Set_Text(L"OH! 스네이크를 다 잡아오셨네용. 이건 제 방패에용. 문어의 공격을 반사할 수 있어용.");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            // CObjMgr::Get_Instance()->Add_Object();
            CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(m_tInfo.fX - 50, m_tInfo.fY, SHIELD, L"ShieldInven"));
            m_bIsItemGived = true;
            break;
        case NPC_QUEST_AFTER:
            CTextBoxMgr::Get_Instance()->Set_Text(L"BYE. 꼭 이세계를 구해주세용");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            break;
        case NPC_QUEST_STATE_END:
            break;
        default:
            break;
        }
        m_ePreState = m_eCurState;
    }
}
