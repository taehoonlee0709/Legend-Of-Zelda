#pragma once
#include "Obj.h"

#define DUNGEON_DOOR_CX  72.f
#define DUNGEON_DOOR_CY  45.f


class CDungeonDoor :
    public CObj
{
public:

    CDungeonDoor() {}
    ~CDungeonDoor() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void CollisionPlayer();
};

