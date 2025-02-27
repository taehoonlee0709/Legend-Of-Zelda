#pragma once
#include "Obj.h"

#define OCTOROCK_BULLET_COLLISIONCX  36.f
#define OCTOROCK_BULLET_COLLISIONCY  36.f
//#define OCTOROK_BULLET_DELAY    300
#define OCTOROCK_BULLET_IMAGE_CX 64
#define OCTOROCK_BULLET_IMAGE_CY 64
#define OCTOROCK_BULLET_LIFETIME 2000
class COctorockBullet :
    public CObj
{
public:
    COctorockBullet() {}
    ~COctorockBullet() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

