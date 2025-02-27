

#pragma once
#include "Obj.h"

#define SNAKE_IMAGE_CX      300
#define SNAKE_IMAGE_CY      300
#define SNAKE_COLLISION_CX     100.f
#define SNAKE_COLLISION_CY     100.f
#define SNAKE_WALK_TIME (2000 + rand() % 1000)


enum MOBLIN_PATTERN { MOBLIN_LEFT, MOBLIN_RIGHT, MOBLIN_DOWN, MOBLIN_UP, MOBLIN_DEAD, MOBLIN_PATTERN_END };

class CMoblin :
    public CObj
{
public:
    CMoblin() :m_ePrePattern(MOBLIN_PATTERN_END), m_eCurPattern(MOBLIN_DOWN) {}
    ~CMoblin() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void		Motion_Change();
    void        Pattern_Change();


private:
    MOBLIN_PATTERN				m_ePrePattern;
    MOBLIN_PATTERN				m_eCurPattern;

    queue<MOBLIN_PATTERN>      m_PatternQueue;
};

