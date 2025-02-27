#pragma once
#include "Obj.h"

#define BRAZIER_CX  48.f
#define BRAZIER_CY  48.f


class CBrazier :
    public CObj
{
public:
    CBrazier() {}
    ~CBrazier() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void ChangeOnOff();
    void CollisionPlayer();
};

