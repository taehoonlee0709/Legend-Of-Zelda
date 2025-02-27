#pragma once
#include "Obj.h"

#define HOME_DOOR_FRAME1_CX  74.f
#define HOME_DOOR_FRAME1_CY  102.f

class CLinkHomeDoor1 :
    public CObj
{
public:
    CLinkHomeDoor1() {}
    ~CLinkHomeDoor1() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

