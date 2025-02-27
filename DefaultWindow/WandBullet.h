
#pragma once
#include "Obj.h"
#define WAND_BULLET_RANGECX  48.f
#define WAND_BULLET_RANGECY  48.f
#define WAND_BULLET_DELAY    350
class CWandBullet :
    public CObj
{
public:
    CWandBullet() : m_dwDelayTime(GetTickCount()) {}
    ~CWandBullet() { }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void		Set_Pos(float _fX, float _fY);

private:
    DWORD m_dwDelayTime;
};

