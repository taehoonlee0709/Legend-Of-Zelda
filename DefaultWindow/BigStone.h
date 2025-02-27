#pragma once
#include "Obj.h"

#define BIG_STONE_CX  130.f
#define BIG_STONE_CY  100.f


class CBigStone :
    public CObj
{
public:

    CBigStone() {}
    ~CBigStone() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void CollisionPlayer();
};

