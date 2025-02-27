#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create(float fX, float fY, float fCX, float fCY)
	{
		CObj* pTerrainObj = new T;

		pTerrainObj->Initialize();
		pTerrainObj->Set_Pos(fX, fY);
		pTerrainObj->Set_Size(fCX, fCY);

		return pTerrainObj;
	}
};

