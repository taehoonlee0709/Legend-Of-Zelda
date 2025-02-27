#pragma once
#include "Obj.h"

#define RSP_IMAGE_CX 200
#define RSP_IMAGE_CY 200

enum COINID { FRONT, BACK, QUESTION_MARK2, COINID_END };

class CCoin :
    public CObj
{
public:
    CCoin() : m_COINID(COINID_END) {}
    ~CCoin() {}

public:
    void Initialize()       override;
    int Update()            override;
    void Late_Update()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

    void    Set_COIN_ID(COINID _eID) { m_COINID = _eID; }
    COINID   Get_COIN_ID() { return m_COINID; }

private:
    COINID m_COINID;
};

