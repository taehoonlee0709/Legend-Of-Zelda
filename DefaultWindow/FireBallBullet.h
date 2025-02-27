#pragma once
#include "Obj.h"
#define FIREBALL_BULLET_COLLISIONCX  50.f
#define FIREBALL_BULLET_COLLISIONCY  50.f
#define FIREBALL_BULLET_IMAGE_CX 50
#define FIREBALL_BULLET_IMAGE_CY 50
#define FIREBALL_BULLET_RENDER_TIME 3000

//#define BOW_BULLET_DELAY    300

class CFireBallBullet :
    public CObj
{
public:
    CFireBallBullet() {}
    ~CFireBallBullet() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

