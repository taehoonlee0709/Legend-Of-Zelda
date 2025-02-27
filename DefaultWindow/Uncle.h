
#pragma once
#include "Obj.h"

#define NPC_SLIDEPUZZLE_CX     48.f
#define NPC_SLIDEPUZZLE_CY     84.f
#define NPC_SLIDEPUZZLE_INTERACTION_RANGE     100

enum NPC_SLIDEPUZZLE_STATE { NPC_SLIDEPUZZLE_IDLE, NPC_SLIDEPUZZLE_BEFORE, NPC_SLIDEPUZZLE_GIVE_ITEM, NPC_SLIDEPUZZLE_AFTER, NPC_SLIDEPUZZLE_STATE_END };

class CUncle :
    public CObj
{
public:
    CUncle() :m_ePreState(NPC_SLIDEPUZZLE_STATE_END), m_eCurState(NPC_SLIDEPUZZLE_IDLE), m_bIsItemGived(false) {}
    ~CUncle() {}

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
    NPC_SLIDEPUZZLE_STATE				m_ePreState;
    NPC_SLIDEPUZZLE_STATE				m_eCurState;
};

