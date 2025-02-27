#pragma once
#include "Obj.h"

#define PRESSURE_BUTTON_CX  48.f
#define PRESSURE_BUTTON_CY  48.f

class CPressureButton :
    public CObj
{
public:
    CPressureButton() {}
    ~CPressureButton() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

