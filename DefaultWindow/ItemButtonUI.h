#pragma once
#include "Obj.h"
#define ITEM_BUTTON_UI_POSX   700.f
#define ITEM_BUTTON_UI_POSY   50.f
#define ITEM_BUTTON_UI_CX     150.f
#define ITEM_BUTTON_UI_CY     80.f
class CItemButtonUI :
    public CObj
{
public:
    CItemButtonUI() {}
    ~CItemButtonUI() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

