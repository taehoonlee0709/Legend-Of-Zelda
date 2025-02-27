#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_FRAME3_CX  240.f
#define DUNGEON_DOOR_FRAME3_CY  30.f

class CDungeonDoorFrame3 :
    public CObj
{
public:
    CDungeonDoorFrame3() {}
    ~CDungeonDoorFrame3() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

