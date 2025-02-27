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
	//�̴ϼȶ������ �������� ���� ��Ȱ��ȭ ��Ų��?
	//�ƴϸ� ������Ʈ ���Ͽ� �ִ� �� �̹����� �־���� Ȱ��ȭ�Ǹ�
}

int CPuzzleMgr::Update()
{
	Zero_TriggerCount();

	return 0;
}

void CPuzzleMgr::Late_Update()
{
	//MyRoad�� ���¸� �ٲ㼭 ������ �� �ְ� ��.//auto iter = CMapObjMgr::Get_Instance()->Get_MapObjList(MOBJ_ROAD).begin();
	if (2 <= m_TriggerCount && 6 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()/*&& 0 != CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).size()*/) // ù ��° ���� ���о ��ư ������
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
	if (18 <= m_TriggerCount && 6 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()) // �� ��° ���� ������ũ ȭ��
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
	if (22 <= m_TriggerCount && 0 >= CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size()) // ����°���� ������ ��, ȭ��
	{
		if (CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_PUZZLE_STAGE_BLOCK).front()->Get_Invincibility() == false)
		{
			CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_PUZZLE_STAGE_BLOCK).front()->Set_Invincibility();
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", SOUND_EFFECT, 1.f);
		}
	}
	//if ( 0 == CObjMgr::Get_Instance()->Get_ObjList(OBJ_MONSTER).size() && 3 <= CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).size()) //����°���� ���ʱ� ������ ������ũ��
	//{

	//	if ((*(++(++(CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).begin()))))->Get_Invincibility() == false)
	//	{
	//		(*(++(++(CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_ROAD).begin()))))->Set_Invincibility();
	//		//CSoundMgr::Get_Instance()->StopSound(CHANNEL_EFFECT);
	//		//CSoundMgr::Get_Instance()->PlaySound(L"PuzzleSolved.wav", CHANNEL_EFFECT, 1.f);
	//	}

	//}
	//if (1 >= CObjMgr::Get_Instance()->Get_ObjList(/*OBJ_OCTOROCK*/OBJ_MONSTER).size() && 2 <= CTerrainObjMgr::Get_Instance()->Get_TerrainObjList(TOBJ_DUNGEON_DOOR).size()) //������ �� ���йݻ� ������ ����.
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
