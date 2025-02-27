#pragma once
#include "Obj.h"

#define GUHU_SALVE_EYE_IMAGE_CX      100
#define GUHU_SALVE_EYE_IMAGE_CY      100
#define GUHU_SALVE_EYE_COLLISION_CX     50.f
#define GUHU_SALVE_EYE_COLLISION_CY     50.f

enum GUHU_SLAVE_EYE_STATE { EYE_STATE_IDLE, EYE_STATE_OPEN_IDLE, EYE_STATE_APPEAR, EYE_STATE_OPEN, EYE_STATE_RAZER, EYE_STATE_DEAD, EYE_STATE_END };

class CGuhuSlaveEye :
    public CObj
{
public:
    CGuhuSlaveEye() :m_bAction(true), m_ePreState(EYE_STATE_END), m_eCurState(EYE_STATE_APPEAR){}
    virtual ~CGuhuSlaveEye() {}

public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

    void        Pattern_Change();
    void		Motion_Change();
    void        Razer();
private:
    bool				    m_bAction;

    GUHU_SLAVE_EYE_STATE		m_ePreState;
    GUHU_SLAVE_EYE_STATE		m_eCurState;

    queue<GUHU_SLAVE_EYE_STATE>      m_PatternQueue;
};

