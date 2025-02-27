#pragma once
#include "Obj.h"

#define TOWN_DOOR_FRAME3_CX  312.f
#define TOWN_DOOR_FRAME3_CY  117.f

class CVillageDoorFrame3 :
    public CObj
{
public:
    CVillageDoorFrame3() {}
    ~CVillageDoorFrame3() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

