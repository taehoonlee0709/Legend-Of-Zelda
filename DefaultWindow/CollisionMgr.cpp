#include "stdafx.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "OctorockBullet.h"
#include "SoundMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float	fWidth = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float	fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float	fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
						Dst->Set_PosY(-fY);

					else
						Dst->Set_PosY(fY);
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Dst->Set_PosX(-fX);

					// 우 충돌
					else
						Dst->Set_PosX(fX);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Monster(list<CObj*> _Player, list<CObj*> _Monster)
{


	float	fX(0.f), fY(0.f);

	for (auto& Player : _Player)
	{
		for (auto& Monster : _Monster)
		{

			if (Check_Rect(Player, Monster, &fX, &fY)) //이미 이 안으로 들어오면 충돌 한 것.
			{


				CPlayer* pTempPlayer = static_cast<CPlayer*>(Player);
				if (pTempPlayer->Get_Invincibility())
					return;
				pTempPlayer->Get_Hit();
				pTempPlayer->Motion_Change();
			}
		}
	}
}

void CCollisionMgr::Collision_Player_MonsterBullet(list<CObj*> _Player, list<CObj*> _MonsterBullet)
{
	float	fX(0.f), fY(0.f);

	for (auto& Player : _Player)
	{
		for (auto& MonsterBullet : _MonsterBullet)
		{

			if (Check_Rect(Player, MonsterBullet, &fX, &fY)) //이미 이 안으로 들어오면 충돌 한 것.
			{
				MonsterBullet->Set_Dead();

				CPlayer* pTempPlayer = static_cast<CPlayer*>(Player);
				if (pTempPlayer->Get_Invincibility())
					return;
				pTempPlayer->Get_Hit();
				pTempPlayer->Motion_Change();

			}
		}
	}
}

CObj* CCollisionMgr::Collision_Player_Door(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				return Src;
			}
		}
	}
	return nullptr;
}

void CCollisionMgr::Collision_PlayerBullet_Monster(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				//Dst
				if (!Src->Get_Invincibility())
				{
					Dst->Set_Invincibility();
					Dst->Set_Dead();
					Src->Set_Hp(-1);
					Src->Set_Invincibility();
				}



				//Src->Set_Dead();


			}
		}
	}
}

void CCollisionMgr::Collision_PlayerBoomerangBullet_Monster(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				//Dst
				if (!Src->Get_Invincibility() && !Dst->Get_Invincibility())
				{
					Dst->Set_Invincibility();
					//Dst->Set_Dead();
					Src->Set_Hp(-1);
					Src->Set_Invincibility();
				}



				//Src->Set_Dead();


			}
		}
	}
}

void CCollisionMgr::Collision_Rect_XY(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rc{};


	for (auto& Dst : _Dst)
	{

		RECT	rcDst{ LONG(Dst->Get_Info().fX - Dst->Get_Info().fCX * 0.5f),
						LONG(Dst->Get_Info().fY - Dst->Get_Info().fCY * 0.5f),
						LONG(Dst->Get_Info().fX + Dst->Get_Info().fCX * 0.5f),
						LONG(Dst->Get_Info().fY + Dst->Get_Info().fCY * 0.5f) };
		for (auto& Src : _Src)
		{
			RECT	rcSrc{ LONG(Src->Get_Info().fX - Src->Get_Info().fCX * 0.5f),
							LONG(Src->Get_Info().fY - Src->Get_Info().fCY * 0.5f),
							LONG(Src->Get_Info().fX + Src->Get_Info().fCX * 0.5f),
							LONG(Src->Get_Info().fY + Src->Get_Info().fCY * 0.5f) };
			if (IntersectRect(&rc, &rcDst, &rcSrc))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Shield(list<CObj*> _Shield, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Shield : _Shield)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Shield->Get_Rect()), &(Src->Get_Rect())))
			{
				Src->Set_Dead();
				//CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD_REPLECT_BULLET,CAbstractFactory<COctorokBullet>)
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Shield_Reflection(list<CObj*> _Shield, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Shield : _Shield)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Shield->Get_Rect()), &(Src->Get_Rect())))
			{
				Src->Set_Dead();
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"MC_Link_Shield_Deflect.wav", SOUND_EFFECT, 2.f);
				CObjMgr::Get_Instance()->Add_Object(OBJ_SHIELD_REFLECT_BULLET, CAbstractFactory<COctorockBullet>::Create(Src->Get_Info().fX, Src->Get_Info().fY, Shield->Get_Angle()));
				
			}
		}
	}
}

void CCollisionMgr::Collision_Obj_Wall(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dst->Get_Info().fY < Src->Get_Info().fY)
						Dst->Set_PosY(-fY);

					else
						Dst->Set_PosY(fY);
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
						Dst->Set_PosX(-fX);

					// 우 충돌
					else
						Dst->Set_PosX(fX);
				}
			}
		}
	}
}

//bool CCollisionMgr::Check_Rect(CObj* _Dst, CMapObj* _Src, float* pX, float* pY)
//{
//	float		fWidth = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
//	float		fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);
//
//	float		fRadiusX = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
//	float		fRadiusY = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f;
//
//	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
//	{
//		*pX = fRadiusX - fWidth;
//		*pY = fRadiusY - fHeight;
//
//		return true;
//	}
//	return false;
//}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* pX, float* pY)
{
	float		fWidth = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float		fHeight = abs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float		fRadiusX = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}
	return false;
}

