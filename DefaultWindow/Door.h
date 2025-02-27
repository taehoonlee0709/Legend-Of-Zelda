#pragma once
#include "Obj.h"
class CDoor :
    public CObj
{
public:
    CDoor() : m_eNextScene(SC_BOSS_STAGE) {}
    CDoor(LINEPOINT& tLTPoint, LINEPOINT& tRBPoint);
    ~CDoor() {}


public:
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;


    SCENEID Get_NextScene() { return  m_eNextScene; }
    // void Enter_The_Door();
    void Set_NextScene(SCENEID _eID) { m_eNextScene = _eID; }
    //void Enter_The_Door();
private:
    SCENEID m_eNextScene;
};
