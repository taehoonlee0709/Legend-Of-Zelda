#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;
	float	fDistance(0.f);

	for (auto& iter : m_ObjList[eID])
	{
		if (iter->Get_Dead())
			continue;

		float	fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;
		float	fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;

		float	fDiagonal = (float)sqrt(fWidth * fWidth + fHeight * fHeight);

		if (!pTarget || (fDistance > fDiagonal))
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	if (300.f < fDistance)
		return nullptr;

	return pTarget;
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int	iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}

			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID	eID = iter->Get_RenderID();
			m_RenderList[eID].push_back(iter);

		}
	}
	//CCollisionMgr::Collision_Rect_XY(m_ObjList[OBJ_PLAYER_BULLET], m_ObjList[OBJ_MONSTER]); // юс╫ц

	CCollisionMgr::Collision_PlayerBullet_Monster(m_ObjList[OBJ_PLAYER_BULLET], m_ObjList[OBJ_MONSTER]); 
	CCollisionMgr::Collision_PlayerBullet_Monster(m_ObjList[OBJ_SHIELD_REFLECT_BULLET], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_PlayerBoomerangBullet_Monster(m_ObjList[OBJ_BOOMERANG_BULLET], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_PlayerBullet_Monster(m_ObjList[OBJ_PLAYER_BULLET], m_ObjList[OBJ_EYE]);
	CCollisionMgr::Collision_Player_MonsterBullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER_BULLET]);
	CCollisionMgr::Collision_Player_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::Collision_Player_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_EYE]);
	//CCollisionMgr::Collision_Player_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_OCTOROK]);
	CCollisionMgr::Collision_Rect_Shield(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER_BULLET]);
	CCollisionMgr::Collision_Rect_Shield_Reflection(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_OCTOROK_BULLET]);
	CCollisionMgr::Collision_Player_MonsterBullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_OCTOROK_BULLET]);

}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{
		m_RenderList[i].sort(
			[](CObj* pDst, CObj* pSrc)->bool
			{
				return pDst->Get_Info().fY < pSrc->Get_Info().fY;
			});

		for (auto& iter : m_RenderList[i])
		{
			iter->Render(hDC);
		}

		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
