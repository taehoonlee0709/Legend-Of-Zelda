#include "stdafx.h"
#include "Malon.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "TextBoxMgr.h"
#include "KeyMgr.h"
#include "RSPMgr.h"
#include "SoundMgr.h"

void CMalon::Initialize()
{
    m_tInfo.fCX = NPC_STAFF_CX;
    m_tInfo.fCY = NPC_STAFF_CY;
    m_eRender = RENDER_GAMEOBJECT;
    CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/NpcStaff.bmp", L"NpcStaff");
    m_pFrameKey = L"NpcStaff";
}

int CMalon::Update()
{
    m_eCurState = NPC_STAFF_IDLE;
    Key_Input();
    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CMalon::Late_Update()
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
    //            CTextBoxMgr::Get_Instance()->Set_Text(L"���� �����п� �ٴ� �� �����ž�... ������ ����ġ�� �ͼ� �����ֶ�...");
    //            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
    //                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
    //            CollisionPlayer();

    //        }

    //    }
    //}
}

void CMalon::Render(HDC hDC)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

    HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

    GdiTransparentBlt(hDC,
        int(m_tInfo.fX - NPC_STAFF_CX * 0.5f) + iScrollX, // ���� ���� ��ġ x, y ��ǥ
        int(m_tInfo.fY - NPC_STAFF_CY * 0.5f) + iScrollY,
        (int)NPC_STAFF_CX,	// ���� ���� ����, ���� ����
        (int)NPC_STAFF_CY,
        hMemDC,		// ������ �̹��� dc
        (int)NPC_STAFF_CX * m_tFrame.iFrameStart,
        (int)NPC_STAFF_CY * m_tFrame.iMotion,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
        (int)NPC_STAFF_CX,	// ������ �̹����� ����, ���� ������
        (int)NPC_STAFF_CY,
        RGB(171, 0, 0));	// �����ϰ��� �ϴ� ����
}

void CMalon::Release()
{
}

void CMalon::CollisionPlayer()
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

void CMalon::Key_Input()
{
    if (0 != CObjMgr::Get_Instance()->Get_ObjList(OBJ_PLAYER).size())
    {
        RECT rc{};
        RECT rcThis{ m_tRect.left,m_tRect.top,m_tRect.right, m_tRect.bottom + NPC_STAFF_INTERACTION_RANGE };
        if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Player()->Get_Rect(), &rcThis))
        {
            if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
            {
                if (true == m_bIsItemGived)
                    m_eCurState = NPC_STAFF_AFTER;
                else if (false == m_bIsItemGived && CRSPMgr::Get_Instance()->Get_IsPlayerWin())
                    m_eCurState = NPC_STAFF_GIVE_ITEM;
                else if (false == m_bIsItemGived && !CRSPMgr::Get_Instance()->Get_IsPlayerWin())
                    m_eCurState = NPC_STAFF_BEFORE;
            }

        }

    }
}

void CMalon::State_Change()
{
    if (m_ePreState != m_eCurState)
    {
        switch (m_eCurState)
        {
        case NPC_STAFF_IDLE:
            break;
        case NPC_STAFF_BEFORE:
            CTextBoxMgr::Get_Instance()->Set_Text(L"��ũ ���ϰ� ������������ �ؼ� �̱�� ������ �������� �ٰ�");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            if (!CRSPMgr::Get_Instance()->Get_IsRSPOpen())
            {
                CRSPMgr::Get_Instance()->Set_IsRSPOpen();
                
            }
            
                CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
                CSoundMgr::Get_Instance()->PlaySound(L"����������.wav", SOUND_EFFECT, 1.f);
      
            break;
        case NPC_STAFF_GIVE_ITEM:
            CTextBoxMgr::Get_Instance()->Set_Text(L"���� ���ִ��� ���ϰ� ���� �� �з� ���忡 ���!! ���ִ� ������ �����Ұ�");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            // CObjMgr::Get_Instance()->Add_Object();
            CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CObjMgr::Get_Instance()->Create_Item(m_tInfo.fX - 50, m_tInfo.fY, WAND, L"StaffInven"));
            m_bIsItemGived = true;
            break;
        case NPC_STAFF_AFTER:
            CTextBoxMgr::Get_Instance()->Set_Text(L"��!");
            if (false == CTextBoxMgr::Get_Instance()->Get_IsTextBoxON())
                CTextBoxMgr::Get_Instance()->Set_IsTextBoxON();
            break;
        case NPC_STAFF_STATE_END:
            break;
        default:
            break;
        }
        m_ePreState = m_eCurState;
    }
}
