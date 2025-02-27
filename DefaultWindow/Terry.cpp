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
    //            //MessageBox(g_hWnd, _T("�������"), _T("�����Ĵ� ������"), MB_OK);
    //            CTextBoxMgr::Get_Instance()->Set_Text(L"������ũ�� ������! ���ָ� ���� �ٰԿ�!");
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
        int(m_tInfo.fX - NPC_QUEST_CX * 0.5f) + iScrollX, // ���� ���� ��ġ x, y ��ǥ
        int(m_tInfo.fY - NPC_QUEST_CY * 0.5f) + iScrollY,
        (int)NPC_QUEST_CX,	// ���� ���� ����, ���� ����
        (int)NPC_QUEST_CY,
        hMemDC,		// ������ �̹��� dc
        (int)NPC_QUEST_CX * m_tFrame.iFrameStart,
        (int)NPC_QUEST_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        (int)NPC_QUEST_CX,	// ������ �̹����� ����, ���� ������
        (int)NPC_QUEST_CY,
        RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
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
        // ���� �浹
        if (fX > fY)
        {
            // �� �浹
            if (this->Get_Info().fY < pPlayer->Get_Info().fY)
            {
                pPlayer->Set_PosY(fY);
            }

            else
            {

                pPlayer->Set_PosY(-fY);
            }
        }
        // �¿� �浹
        else
        {
            // �� �浹
            if (this->Get_Info().fX < pPlayer->Get_Info().fX)
            {

                pPlayer->Set_PosX(fX);
            }

            // �� �浹
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
            CTextBoxMgr::Get_Instance()->Set_Text(L"OH! ������ũ�� �� ��ƿ��̳׿�. �̰� �� ���п���. ������ ������ �ݻ��� �� �־��.");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            // CObjMgr::Get_Instance()->Add_Object();
            CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(m_tInfo.fX - 50, m_tInfo.fY, SHIELD, L"ShieldInven"));
            m_bIsItemGived = true;
            break;
        case NPC_QUEST_AFTER:
            CTextBoxMgr::Get_Instance()->Set_Text(L"BYE. �� �̼��踦 �����ּ���");
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
