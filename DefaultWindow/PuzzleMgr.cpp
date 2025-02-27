#include "stdafx.h"
#include "PuzzleMgr.h"
#include "TerrainObjMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"

CPuzzleMgr* CPuzzleMgr::m_pInstance = nullptr;

CPuzzleMgr::CPuzzleMgr() : m_TriggerCount(0)
{
}

CPuzzleMgr::~CPuzzleMgr()
{
	Release();
}

void CPuzzleMgr::Initialize()
{
	//이니셜라이즈에서 보스가는 문을 비활성화 시킨다?
	//아니면 오브젝트 파일에 있는 문 이미지를 넣어놓고 활성화되면
}

int CPuzzleMgr::Update()
{
	Zero_TriggerCount();

	return 0;
}

void CPuzzleMgr::Late_Update()
{
	//MyRoad의 상태를 바꿔서 지나갈 수 있게 함.//auto iter = CMapObjMgr::Get_Instance()->Get_MapObjList(MOBJ_ROAD).begin();
	if (2 <= m_TriggerCount && 6 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()/*&& 0 != CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).size()*/) // 첫 번째 구간 돌밀어서 버튼 누르기
	{
		
		if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).front()->Get_Invincibility() == false)
		{
			CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).front()->Set_Invincibility();
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
		}
		//if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).front()->Get_Invincibility() == false)
		//{
		//	CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).front()->Set_Invincibility();
		//	//CSoundMgr::Get_Instance()->StopSound(CHANNEL_EFFECT);
		//	//CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", CHANNEL_EFFECT, 1.f);
		//}

	}
	if (18 <= m_TriggerCount && 6 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()) // 두 번째 구간 스네이크 화살
	{	
		if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).front()->Get_Invincibility() == false)
		{
			CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).front()->Set_Invincibility();
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
		}
		/*auto& iter = CMapObjMgr::Get_Instance()->Get_MapObjList(MOBJ_ROAD).begin();
		++iter;
		bool bActivation = (*iter)->Get_Invincibility();
		if(bActivation ==false)
			(*iter)->Set_Invincibility();*/
		//if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).front()->Get_Invincibility() == false)
		//{
		//	CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).front()->Set_Invincibility();
		//	//CSoundMgr::Get_Instance()->StopSound(CHANNEL_EFFECT);
		//	//CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", CHANNEL_EFFECT, 1.f);
		//}
		//
	}
	if (22 <= m_TriggerCount && 0 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()) // 세번째구간 오른쪽 길, 화로
	{
		if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_PUZZLE_STAGE_BLOCK).front()->Get_Invincibility() == false)
		{
			CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_PUZZLE_STAGE_BLOCK).front()->Set_Invincibility();
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
		}
	}
	//if ( 0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size() && 3 <= CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).size()) //세번째구간 왼쪽길 오른쪽 스네이크들
	//{

	//	if ((*(++(++(CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).begin()))))->Get_Invincibility() == false)
	//	{
	//		(*(++(++(CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).begin()))))->Set_Invincibility();
	//		//CSoundMgr::Get_Instance()->StopSound(CHANNEL_EFFECT);
	//		//CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", CHANNEL_EFFECT, 1.f);
	//	}

	//}
	//if (1 >= CObjMgr::Get_Instance()->Get_ObjList(/*OBJ_OCTOROCK*/OBJ_MONSTER).size() && 2 <= CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).size()) //마지막 문 방패반사 성공시 열림.
	//{
	//	if ((*(++(CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).begin())))->Get_Invincibility() == false)
	//	{
	//		(*(++(CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).begin())))->Set_Invincibility();
	//		//CSoundMgr::Get_Instance()->StopSound(CHANNEL_EFFECT);
	//		//CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", CHANNEL_EFFECT, 1.f);
	//	}

	//}
}

void CPuzzleMgr::Render(HDC hDC)
{
}

void CPuzzleMgr::Release()
{
}
