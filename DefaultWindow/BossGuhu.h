#pragma once
#include "Obj.h"
#include "Define.h"
#define BOSS_GUHU_POSX  2000.f
#define BOSS_GUHU_POSY  1700.f
#define BOSS_GUHU_IMAGE_CX      300.f
#define BOSS_GUHU_IMAGE_CY      300.f
#define BOSS_GUHU_COLLISION_CX     130.f
#define BOSS_GUHU_COLLISION_CY     170.f

#define IDLE_PATTERN_TIME 3000
#define EYES_SPAWN_PATTERN_TIME 600
#define FIREBALL_PATTERN_TIME 1500
#define TELEPORT_PATTERN_TIME 1500
#define ROTATE_EYES_TIME 2400

enum BOSSPATTERN { BOSSPATTERN_IDLE, BOSSPATTERN_HIT, BOSSPATTERN_FIREBALL, BOSSPATTERN_TELEPORT, BOSSPATTERN_SPAWN_EYES, BOSSPATTERN_ROTATE_EYES, BOSSPATTERN_END };

class CBossGuhu :
    public CObj
{
public:
    CBossGuhu():m_bAction(false) , m_ePrePattern(BOSSPATTERN_END) , m_eCurPattern(BOSSPATTERN_IDLE), m_dwBulletCoolTime(GetTickCount()),
        m_iBulletCount(0)
    {}
    ~CBossGuhu() {}
public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    void		Motion_Change();
    void        Pattern_Change();

public:
    void        FireBall();
    void        Teleport();
    void        Spawn_Eyes();
    void        Rotate_Eyes();
    void        Check_Eyes();

    template<typename T>
    CObj* Create_Bullet(float fX, float fY, float fAngle, DWORD dwTime);

private:
    bool				    m_bAction;
    int                     m_iBulletCount;
    DWORD                   m_dwBulletCoolTime;

    BOSSPATTERN				m_ePrePattern;
    BOSSPATTERN				m_eCurPattern;

    queue<BOSSPATTERN>      m_PatternQueue;
    list<CObj*>             m_GuhuEyeList;
};

template<typename T>
inline CObj* CBossGuhu::Create_Bullet(float fX, float fY, float fAngle, DWORD dwTime)
{
    CObj* pBullet = new T;

    pBullet->Initialize();
    pBullet->Set_Angle(fAngle);
    pBullet->Set_Pos(fX, fY);
    pBullet->Set_MotionTime(dwTime);

    return pBullet;
}
