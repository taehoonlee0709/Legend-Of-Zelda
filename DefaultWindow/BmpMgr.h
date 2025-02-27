#pragma once

#include "MyBmp.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	static		CBmpMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void	Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC		Find_Image(const TCHAR* pImgKey);
	void	Release();

private:
	map<const TCHAR*, CMyBmp*>		m_mapBit;
	static CBmpMgr*	m_pInstance;
};

