#pragma once
#include "Obj.h"


#define SWORD_EFFECT_IMAGE_CX  100.f
#define SWORD_EFFECT_IMAGE_CY  100.f

class CSwordEffect :
    public CObj
{
public:
    CSwordEffect() {}
    ~CSwordEffect() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

