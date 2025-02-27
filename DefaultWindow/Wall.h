#pragma once
#include "Define.h"
#include "Obj.h"
class CWall :
    public CObj
{
public:
    CWall() {}
    CWall(LINEPOINT& tLTPoint, LINEPOINT& tRBPoint);
    virtual ~CWall() { Release(); }

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
};

