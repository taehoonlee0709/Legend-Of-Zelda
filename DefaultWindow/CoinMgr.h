
#pragma once
#include "Obj.h"
#include "Coin.h"

#define PLAYER_ROCK_POSX 200
#define PLAYER_ROCK_POSY 450

#define PLAYER_SCISSORS_POSX 400
#define PLAYER_SCISSORS_POSY 450

#define PLAYER_PAPER_POSX 600
#define PLAYER_PAPER_POSY 450

#define RSP_CURSOR_CX 100
#define RSP_CURSOR_CY 100

class CCoinMgr
{

private:
	CCoinMgr() :m_bIsCoinOpen(false), m_bIsPlayerWin(false), m_iCursor(0), m_AICoin(nullptr), m_bIsEnter(false), m_szResult(L"") {}
	~CCoinMgr() { Release(); }

public:
	void		Initialize();
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

public:
	void	Key_Input();
	void	Check_Coin();


	void	Set_IsCoinOpen() { m_bIsCoinOpen = !m_bIsCoinOpen; }
	bool	Get_IsCoinOpen() { return m_bIsCoinOpen; }

	void	Set_IsPlayerWin() { m_bIsPlayerWin = !m_bIsPlayerWin; }
	bool	Get_IsPlayerWin() { return m_bIsPlayerWin; }

	vector<CObj*> Get_Vector() { return m_vecPlayerCoin; }

	CObj* Create_Coin(float _fX, float _fY, TCHAR* _szFrameKey, COINID _eID);

private:
	bool		m_bIsCoinOpen;
	bool		m_bIsPlayerWin;
	bool		m_bIsEnter;
	int			m_iCursor;
	TCHAR* m_szResult;
	CObj* m_AICoin;
	vector<CObj*> m_vecPlayerCoin;


public:
	static CCoinMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CCoinMgr;

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
	static CCoinMgr* m_pInstance;
};

