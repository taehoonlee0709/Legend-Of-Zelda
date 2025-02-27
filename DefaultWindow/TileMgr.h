#pragma once

#include "Tile.h"

class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	static		CTileMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;

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
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Picking(POINT pt, int _iDrawID, int _iOption);

public:
	void		Save_Tile();
	void		Load_Tile();

private:
	static CTileMgr*	m_pInstance;
	vector<CObj*>		m_vecTile;

};

