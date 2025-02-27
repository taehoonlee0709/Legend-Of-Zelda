#pragma once
#include "Define.h"

class CBossPuzzleMgr
{
private:
	CBossPuzzleMgr();
	~CBossPuzzleMgr();

public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Zero_TriggerCount() { m_TriggerCount = 0; }
	void		Set_TriggerCount() { ++m_TriggerCount; }
	size_t		Get_TriggerCount() { return m_TriggerCount; }

private:
	size_t	m_TriggerCount;



public:
	static CBossPuzzleMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBossPuzzleMgr;

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
	static CBossPuzzleMgr* m_pInstance;
};

