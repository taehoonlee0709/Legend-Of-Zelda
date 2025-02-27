#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_FRAME4_CX  132.f
#define DUNGEON_DOOR_FRAME4_CY  96.f

class CDungeonDoorFrame4 :
    public CObj
{
public:
    CDungeonDoorFrame4() {}
    ~CDungeonDoorFrame4() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

