
#pragma once
#include "Obj.h"

#define HOME_DOOR_FRAME2_CX  110.f
#define HOME_DOOR_FRAME2_CY  90.f

class CLinkHomeDoor2 :
    public CObj
{
public:
    CLinkHomeDoor2() {}
    ~CLinkHomeDoor2() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};


