#pragma once
#include "Obj.h"
#include "RSP.h"

#define PLAYER_ROCK_POSX 200
#define PLAYER_ROCK_POSY 450

#define PLAYER_SCISSORS_POSX 400
#define PLAYER_SCISSORS_POSY 450

#define PLAYER_PAPER_POSX 600
#define PLAYER_PAPER_POSY 450

#define RSP_CURSOR_CX 100
#define RSP_CURSOR_CY 100

class CRSPMgr
{

private:
	CRSPMgr():m_bIsRSPOpen(false), m_bIsPlayerWin(false), m_iCursor(0), m_AIRSP(nullptr), m_bIsEnter(false),m_szResult(L"") {}
	~CRSPMgr() { Release(); }

public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	void	Key_Input();
	void	Check_RSP();


	void	Set_IsRSPOpen() { m_bIsRSPOpen = !m_bIsRSPOpen; }
	bool	Get_IsRSPOpen() { return m_bIsRSPOpen; }

	void	Set_IsPlayerWin() { m_bIsPlayerWin = !m_bIsPlayerWin; }
	bool	Get_IsPlayerWin() { return m_bIsPlayerWin; }

	vector<CObj*> Get_Vector() { return m_vecPlayerRSP; }

	CObj* Create_RSP(float _fX,float _fY, TCHAR* _szFrameKey, RSPID _eID);

private:
	bool		m_bIsRSPOpen;	
	bool		m_bIsPlayerWin;
	bool		m_bIsEnter;
	int			m_iCursor;
	TCHAR*		m_szResult;
	CObj*		m_AIRSP;
	vector<CObj*> m_vecPlayerRSP;


public:
	static CRSPMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CRSPMgr;

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
	static CRSPMgr* m_pInstance;
};

