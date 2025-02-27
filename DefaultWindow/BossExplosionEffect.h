#pragma once
#include "Obj.h"

#define BOSS_EXPLOSION_EFFECT_RANGECX  250.f
#define BOSS_EXPLOSION_EFFECT_RANGECY  250.f

class CBossExplosionEffect :
    public CObj
{
public:
    CBossExplosionEffect() {}
    ~CBossExplosionEffect() {}
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

