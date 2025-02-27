#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_FRAME2_CX   144.f
#define DUNGEON_DOOR_FRAME2_CY   192.f

class CDungeonDoorFrame2 :
    public CObj
{
public:
    CDungeonDoorFrame2() {}
    ~CDungeonDoorFrame2() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

