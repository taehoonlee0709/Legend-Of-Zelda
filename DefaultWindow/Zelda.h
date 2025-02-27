
#pragma once
#include "Obj.h"

#define NPC_ZELDA_CX     200.f
#define NPC_ZELDA_CY     200.f
#define NPC_ZELDA_INTERACTION_RANGE     50

enum NPC_ZELDA_STATE { NPC_ZELDA_IDLE, NPC_ZELDA_BEFORE, NPC_ZELDA_GIVE_ITEM, NPC_ZELDA_AFTER, NPC_ZELDA_STATE_END };


class CZelda :
    public CObj
{
public:
    CZelda() :m_ePreState(NPC_ZELDA_STATE_END), m_eCurState(NPC_ZELDA_IDLE), m_bIsItemGived(false) {}
    ~CZelda() {}
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
    bool                        m_bIsItemGived;
    NPC_ZELDA_STATE				m_ePreState;
    NPC_ZELDA_STATE				m_eCurState;
};

