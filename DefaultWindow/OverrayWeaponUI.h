#pragma once
#include "Obj.h"
#include "Item.h"
#define OVERRAY_WEAPON_UI_CX     48.f
#define OVERRAY_WEAPON_UI_CY     48.f

class COverrayWeaponUI :
    public CObj
{
public:
    COverrayWeaponUI() {}
    ~COverrayWeaponUI() {}

public:
    virtual void    Initialize()    override;
    virtual int     Update()        override;
    virtual void    Late_Update()    override;
    virtual void    Render(HDC hDC) override;
    virtual void    Release()       override;

    void    ChangeWeapon(ITEMCODE _eItemcode);
};

