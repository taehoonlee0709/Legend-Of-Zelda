#pragma once
#include "Scene.h"
class CFinalStage :
    public CScene
{
public:
    CFinalStage();
    virtual ~CFinalStage();

public:
    virtual void Initialize()       override;
    virtual int Update()            override;
    virtual void Late_Update()       override;
    virtual void Render(HDC hDC)    override;
    virtual void Release()          override;
};

