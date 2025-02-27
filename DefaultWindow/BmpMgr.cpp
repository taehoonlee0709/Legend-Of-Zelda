#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), 
		[&](auto& MyPair)->bool 
	{
		if (!lstrcmp(MyPair.first, pImgKey))
			return true;
				
		return false;
	});

	if (iter == m_mapBit.end())
	{
		CMyBmp*	pBmp = new CMyBmp;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}
}

HDC CBmpMgr::Find_Image(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(),
		[&](auto& MyPair)->bool
	{
		if (!lstrcmp(MyPair.first, pImgKey))
			return true;

		return false;
	});

	if (iter == m_mapBit.end())
	{
		MessageBox(g_hWnd, pImgKey, L"NO Texture", MB_OK);

		return nullptr;
	}

	return iter->second->Get_MemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	});

	m_mapBit.clear();
}
