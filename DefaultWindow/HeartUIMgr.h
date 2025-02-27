#pragma once
#include "Obj.h"



class CHeartUIMgr
{
private:
	CHeartUIMgr();
	~CHeartUIMgr();

public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	//void		Render(HDC hDC);
	//void		Release();

	void		Minus_Hp();

private:
	list<CObj*> m_HeartUIList;
	int m_iCursor;

public:
	static CHeartUIMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CHeartUIMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CHeartUIMgr* m_pInstance;
};

