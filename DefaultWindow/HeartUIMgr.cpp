#include "stdafx.h"
#include "HeartUIMgr.h"
#include "ObjMgr.h"
#include "HeartUI.h"

CHeartUIMgr* CHeartUIMgr::m_pInstance = nullptr;


CHeartUIMgr::CHeartUIMgr() :m_iCursor(0)
{
}

CHeartUIMgr::~CHeartUIMgr()
{
}

void CHeartUIMgr::Initialize()
{
	m_iCursor = 3;
	list<CObj*>::iterator iter = CObjMgr::Get_Instance()->Get_ObjList_Begin(OBJ_UI);


	m_HeartUIList.push_back(*(iter++));
	m_HeartUIList.push_back(*(iter++));
	m_HeartUIList.push_back(*(iter++));
	m_HeartUIList.push_back(*(iter++));
	m_HeartUIList.push_back(*(iter));

}

int CHeartUIMgr::Update()
{
	return 0;
}

void CHeartUIMgr::Late_Update()
{
	int iPlayerHp = CObjMgr::Get_Instance()->Get_Player()->Get_Hp();
	if (0 == iPlayerHp % 4)
		m_iCursor = int(iPlayerHp / 4) - 1;
	else
		m_iCursor = int(iPlayerHp / 4);
}

void CHeartUIMgr::Minus_Hp()
{
	auto iter = m_HeartUIList.begin();

	for (int i = 0; m_iCursor > i; ++i)
	{
		++iter;
	}

	static_cast<CHeartUI*>(*iter)->Move_Frame();
}
