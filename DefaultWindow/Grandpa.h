
#pragma once
#include "Obj.h"

#define NPC_SMITH_CX     200.f
#define NPC_SMITH_CY     200.f
#define NPC_SMITH_INTERACTION_RANGE     50

enum NPC_SMITH_STATE { NPC_SMITH_IDLE, NPC_SMITH_BEFORE, NPC_SMITH_GIVE_ITEM, NPC_SMITH_AFTER, NPC_SMITH_STATE_END };


class CGrandpa :
    public CObj
{
public:
    CGrandpa() :m_ePreState(NPC_SMITH_STATE_END), m_eCurState(NPC_SMITH_IDLE), m_bIsItemGived(false) {}
    ~CGrandpa() {}
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
    NPC_SMITH_STATE				m_ePreState;
    NPC_SMITH_STATE				m_eCurState;
};

