#pragma once
#include "Obj.h"
#define SWORD_BULLET_RANGECX  120.f
#define SWORD_BULLET_RANGECY  80.f


class CSwordBullet :
    public CObj
{
public:
    CSwordBullet() {}
    ~CSwordBullet() {  }
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    virtual void		Set_Pos(float _fX, float _fY);

    //void    Set_Hit() { m_bHit = !m_bHit; }

//private:
//    bool    m_bHit;
};

