#pragma once
#include "Obj.h"

#define RSP_IMAGE_CX 200
#define RSP_IMAGE_CY 200

enum RSPID {ROCK,SCISSORS,PAPER,QUESTION_MARK,RSPID_END};

class CRSP :
    public CObj
{
public:
    CRSP() : m_RSPID(RSPID_END) {}
    ~CRSP() {}

public:
    void Initialize()       override;
    int Update()            override;
    void Late_Update()       override;
    void Render(HDC hDC)    override;
    void Release()          override;

    void    Set_RSP_ID(RSPID _eID)    { m_RSPID = _eID; }
    RSPID   Get_RSP_ID()              { return m_RSPID; }

private:
    RSPID m_RSPID;
};

