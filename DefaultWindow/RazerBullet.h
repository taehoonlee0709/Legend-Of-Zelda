#pragma once
#include "Obj.h"

#define RAZER_BULLET_COLLISIONCX  30.f
#define RAZER_BULLET_COLLISIONCY  250.f
#define RAZER_BULLET_IMAGE_CX 50
#define RAZER_BULLET_IMAGE_CY 250
#define RAZER_BULLET_RENDER_TIME 3000

class CRazerBullet :
    public CObj
{
public:
    CRazerBullet() {}
    ~CRazerBullet() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


};

