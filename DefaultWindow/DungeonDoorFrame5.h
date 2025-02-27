
#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_FRAME5_CX  240.f
#define DUNGEON_DOOR_FRAME5_CY  234.f

class CDungeonDoorFrame5 :
    public CObj
{
public:
    CDungeonDoorFrame5() {}
    ~CDungeonDoorFrame5() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

