#pragma once
#include "Obj.h"

#define ROAD_CX  96.f
#define ROAD_CY  192.f

class CRoad :
    public CObj
{
public:
    CRoad() {}
    ~CRoad() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void CollisionPlayer();
};

