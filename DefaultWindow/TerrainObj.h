#pragma once
#include "Define.h"
class CTerrainObj
{
public:
	CTerrainObj()
	{
		ZeroMemory(&m_tInfo, sizeof(INFO));
		ZeroMemory(&m_tRect, sizeof(RECT));
	}
	virtual ~CTerrainObj() {}

public:
	virtual void Initialize()	PURE;
	virtual int  Update()		PURE;
	virtual void Late_Update()	PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release()		PURE;

public:
	INFO		Get_Info() { return m_tInfo; }
	RECT		Get_Rect() { return m_tRect; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}
	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

protected:
	void		Update_Rect();

protected:
	INFO			m_tInfo;
	RECT			m_tRect;
};

