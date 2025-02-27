#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_FRAME1_CX  144.f
#define DUNGEON_DOOR_FRAME1_CY  192.f

class CDungeonDoorFrame1 :
    public CObj
{
public:
    CDungeonDoorFrame1() {}
    ~CDungeonDoorFrame1() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

