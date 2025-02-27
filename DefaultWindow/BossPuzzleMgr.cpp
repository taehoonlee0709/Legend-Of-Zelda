#include "stdafx.h"
#include "BossPuzzleMgr.h"
#include "TerrainObjMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

CBossPuzzleMgr* CBossPuzzleMgr::m_pInstance = nullptr;

CBossPuzzleMgr::CBossPuzzleMgr() : m_TriggerCount(0)
{
}

CBossPuzzleMgr::~CBossPuzzleMgr()
{
	Release();
}

void CBossPuzzleMgr::Initialize()
{
	//이니셜라이즈에서 보스가는 문을 비활성화 시킨다?
	//아니면 오브젝트 파일에 있는 문 이미지를 넣어놓고 활성화되면
}

int CBossPuzzleMgr::Update()
{
	Zero_TriggerCount();

	return 0;
}

void CBossPuzzleMgr::Late_Update()
{
	
	if (0 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()) 
	{
		if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_BIG_STONE).front()->Get_Invincibility() == false)
		{
			CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_BIG_STONE).front()->Set_Invincibility();
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
		}
	}
}

void CBossPuzzleMgr::Render(HDC hDC)
{
}

void CBossPuzzleMgr::Release()
{
}
