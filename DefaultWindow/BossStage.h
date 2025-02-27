#pragma once
#include "Scene.h"

#define BOSS_STAGE_MAX_SCREENX 1216
#define BOSS_STAGE_MAX_SCREENY 896
#define BOSS_STAGE_PLAYER_SPAWNX 600.f
#define BOSS_STAGE_PLAYER_SPAWNY 560.f
class CBossStage :
    public CScene
{
public:
    CBossStage();
    virtual ~CBossStage();

public:
    virtual void Initialize()       override;
    virtual int Update()            override;
    virtual void Late_Update()       override;
    virtual void Render(HDC hDC)    override;
    virtual void Release()          override;
};

