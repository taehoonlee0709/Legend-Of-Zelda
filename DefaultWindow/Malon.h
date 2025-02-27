#pragma once
#include "Obj.h"

#define NPC_STAFF_CX     57.f
#define NPC_STAFF_CY     72.f
#define NPC_STAFF_INTERACTION_RANGE     50

enum NPC_STAFF_STATE { NPC_STAFF_IDLE, NPC_STAFF_BEFORE, NPC_STAFF_GIVE_ITEM, NPC_STAFF_AFTER, NPC_STAFF_STATE_END };


class CMalon :
    public CObj
{
public:
    CMalon() :m_ePreState(NPC_STAFF_STATE_END), m_eCurState(NPC_STAFF_IDLE), m_bIsItemGived(false) {}
    ~CMalon() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void CollisionPlayer();
    void Key_Input();
    void State_Change();

private:
    bool                                m_bIsItemGived;
    NPC_STAFF_STATE				m_ePreState;
    NPC_STAFF_STATE				m_eCurState;
    DWORD m_dwBulletCoolTime;

};

