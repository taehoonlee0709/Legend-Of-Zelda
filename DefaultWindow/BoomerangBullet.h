#pragma once
#include "Obj.h"

#define BOOMERANG_BULLET_COLLISIONCX  48.f
#define BOOMERANG_BULLET_COLLISIONCY  48.f
#define BOOMERANG_BULLET_DELAY    200
#define BOOMERANG_BULLET_IMAGE_CX 48
#define BOOMERANG_BULLET_IMAGE_CY 48

class CBoomerangBullet :
    public CObj
{

public:
    CBoomerangBullet() : m_dwDelayTime(GetTickCount()) {}
    ~CBoomerangBullet() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    virtual void		Set_Pos(float _fX, float _fY);

private:
    DWORD m_dwDelayTime;
};

