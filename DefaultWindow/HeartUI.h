#pragma once
#include "Obj.h"

#define HEART_UI_POSX   50.f
#define HEART_UI_POSY   30.f
#define HEART_UI_CX     30.f
#define HEART_UI_CY     30.f
class CHeartUI :
    public CObj
{
public:
    CHeartUI() {}
    ~CHeartUI() {}


public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    void Move_Frame();
};

