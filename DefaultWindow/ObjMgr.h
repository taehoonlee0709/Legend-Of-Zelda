#pragma once

#include "Obj.h"
#include "Item.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj* Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj* Get_Boss() { return m_ObjList[OBJ_BOSS].front(); }

	CObj* Get_Target(OBJID eID, CObj* pObj);
	list<CObj*> Get_ObjList(OBJID eID) { return  m_ObjList[eID]; }
	list<CObj*>::iterator Get_ObjList_Begin(OBJID eID) { return  m_ObjList[eID].begin(); }
	list<CObj*> Get_RenderList(RENDERID eID) { return  m_RenderList[eID]; }
	void	PushBack_RenderList(RENDERID eID, CObj* pObj) { m_RenderList[eID].push_back(pObj); }
	void	Clear_RenderList() {
		for (size_t i = 0; i < RENDER_END; ++i)
			m_RenderList[i].clear();
	}
public:
	void	Add_Object(OBJID eID, CObj* pObj);


	int		Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	CObj* Create_Item(float fX, float fY, ITEMCODE ItemCode, TCHAR* pFrameKey)
	{
		CObj* pObj = new CItem;

		pObj->Initialize();
		pObj->Set_Pos(fX, fY);
		static_cast<CItem*>(pObj)->Set_ItemCode(ItemCode);
		pObj->Set_FrameKey(pFrameKey);

		return pObj;
	}

	template<typename T>
	CObj* Create_Effect(float fX, float fY);//, float fAngle

	void	Delete_ID(OBJID eID);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_RenderList[RENDER_END];

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CObjMgr* m_pInstance;
};

template<typename T>
inline CObj* CObjMgr::Create_Effect(float fX, float fY)//, float fAngle
{
	CObj* pBullet = new T;

	pBullet->Initialize();
	//pBullet->Set_Angle(fAngle);
	pBullet->Set_Pos(fX, fY);
	//pBullet->Set_MotionTime(dwTime);

	return pBullet;
}