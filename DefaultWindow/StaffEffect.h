#pragma once
#include "Obj.h"

#define STAFF_EFFECT_IMAGE_CX  70.f
#define STAFF_EFFECT_IMAGE_CY  70.f


class CStaffEffect :
    public CObj
{
public:
    CStaffEffect() {}
    ~CStaffEffect() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

