#pragma once
#include "Obj.h"

#define TOWN_DOOR_FRAME2_CX  336.f
#define TOWN_DOOR_FRAME2_CY  177.f

class CVillageDoorFrame2 :
    public CObj
{
public:
    CVillageDoorFrame2() {}
    ~CVillageDoorFrame2() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
