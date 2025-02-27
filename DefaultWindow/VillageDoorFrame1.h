#pragma once
#include "Obj.h"

#define TOWN_DOOR_FRAME1_CX  384.f
#define TOWN_DOOR_FRAME1_CY  24.f

class CVillageDoorFrame1 :
    public CObj
{
public:
    CVillageDoorFrame1() {}
    ~CVillageDoorFrame1() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};
