#pragma once
#include "Obj.h"

#define SNAKE_IMAGE_CX      100
#define SNAKE_IMAGE_CY      100
#define SNAKE_COLLISION_CX     60.f
#define SNAKE_COLLISION_CY     60.f
#define SNAKE_WALK_TIME (2000 + rand() % 1000)


enum SNAKE_PATTERN { SNAKE_LEFT, SNAKE_RIGHT, SNAKE_DOWN, SNAKE_UP, SNAKE_DEAD, SNAKE_PATTERN_END };

class CSnake :
    public CObj
{
public:
    CSnake() :m_ePrePattern(SNAKE_PATTERN_END), m_eCurPattern(SNAKE_DOWN) {}
    ~CSnake() {}

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void		Motion_Change();
    void        Pattern_Change();


private:
    SNAKE_PATTERN				m_ePrePattern;
    SNAKE_PATTERN				m_eCurPattern;

    queue<SNAKE_PATTERN>      m_PatternQueue;
};

