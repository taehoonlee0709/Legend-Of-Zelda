#pragma once
#include "Obj.h"

#define MOVABLE_STONE_CX  48.f
#define MOVABLE_STONE_CY  48.f


class CMovableStone :
    public CObj
{
public:
    CMovableStone() {}
    ~CMovableStone() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void CollisionPlayer();
};

