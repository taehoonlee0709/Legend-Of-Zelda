#pragma once
#include "Obj.h"

#define NPC_QUEST_CX     100.f
#define NPC_QUEST_CY     100.f
#define NPC_QUEST_INTERACTION_RANGE     50

enum NPC_QUEST_STATE { NPC_QUEST_IDLE, NPC_QUEST_BEFORE, NPC_QUEST_GIVE_ITEM, NPC_QUEST_AFTER, NPC_QUEST_STATE_END };

class CTerry :
    public CObj
{
public:
    CTerry() :m_ePreState(NPC_QUEST_STATE_END), m_eCurState(NPC_QUEST_IDLE), m_bIsItemGived(false) {}
    ~CTerry() {}

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
    NPC_QUEST_STATE				m_ePreState;
    NPC_QUEST_STATE				m_eCurState;
};

