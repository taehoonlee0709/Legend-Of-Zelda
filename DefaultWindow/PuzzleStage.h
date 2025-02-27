#pragma once
#include "Scene.h"


#define PUZZLE_STAGE_MAX_SCREENX 1776 
#define PUZZLE_STAGE_MAX_SCREENY 5232
#define PUZZLE_STAGE_PLAYER_SPAWNX 890
#define PUZZLE_STAGE_PLAYER_SPAWNY 5100

#define PUZZLE_STAGE_SECTION1_SNAKE_SPAWNX 80
#define PUZZLE_STAGE_SECTION1_SNAKE_SPAWNY 2505


#define PUZZLE_STAGE_SECTION2_SNAKE_SPAWNX 1300
#define PUZZLE_STAGE_SECTION2_SNAKE_SPAWNY 1270

#define PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNX 580
#define PUZZLE_STAGE_SECTION2_OCTOROK_SPAWNY 1200

class CPuzzleStage :
    public CScene
{
public:
    CPuzzleStage() {}
    ~CPuzzleStage() {}
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

