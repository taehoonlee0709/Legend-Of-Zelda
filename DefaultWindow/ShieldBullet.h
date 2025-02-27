#pragma once
#include "Obj.h"
#define SHIELD_BULLET_RANGECX  90.f
#define SHIELD_BULLET_RANGECY  80.f

class CShieldBullet :
    public CObj
{
public:
    CShieldBullet() {}
    ~CShieldBullet() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void		Set_Pos(float _fX, float _fY);
};

