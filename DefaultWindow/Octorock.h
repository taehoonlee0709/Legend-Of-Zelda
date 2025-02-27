#pragma once
#include "Obj.h"

#define OCTOROCK_IMAGE_CX      128
#define OCTOROCK_IMAGE_CY      128
#define OCTOROCK_COLLISION_CX     64.f
#define OCTOROCK_COLLISION_CY     64.f
#define OCTOROCK_BULLET_DELAY 100
class COctorock :
    public CObj
{
public:
    COctorock() : m_dwBulletCoolTime(GetTickCount()) {}
    ~COctorock() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Motion();

private:
    DWORD m_dwBulletCoolTime;
    DWORD m_dwShoot_Delay;
};



