#pragma once

#include "Define.h"
#include "Obj.h"
#include "TerrainObj.h"

#define		PLAYER_KNOCKBACK_SIZE	100.f

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void		Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src);

	static void		Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src);
	static	bool	Check_Sphere(CObj* _Dst, CObj* _Src);

	static void		Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static	bool	Check_Rect(CObj* _Dst, CObj* _Src, float* pX, float* pY);



public:
	static void		Collision_Player_Monster(list<CObj*> _Dst, list<CObj*> _Src);
	static void     Collision_Player_MonsterBullet(list<CObj*> _Dst, list<CObj*> _Src);
	static CObj* Collision_Player_Door(list<CObj*> _Dst, list<CObj*> _Src);

	static void		Collision_PlayerBullet_Monster(list<CObj*> _Dst, list<CObj*> _Src);
	static void		Collision_PlayerBoomerangBullet_Monster(list<CObj*> _Dst, list<CObj*> _Src);

	static void		Collision_Rect_XY(list<CObj*> _Dst, list<CObj*> _Src);
	static void		Collision_Rect_Shield(list<CObj*> _Dst, list<CObj*> _Src);
	static void		Collision_Rect_Shield_Reflection(list<CObj*> _Dst, list<CObj*> _Src);

	static void		Collision_Obj_Wall(list<CObj*> _Dst, list<CObj*> _Src);
	//static void		Collision_Obj_Wall(list<CObj*> _Dst, list<CMapObj*> _Src);
	//static	bool	Check_Rect(CObj* _Dst, CMapObj* _Src, float* pX, float* pY);

};

