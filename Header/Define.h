#pragma once

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0
#define			PI			3.14f

#define			TILEX		30
#define			TILEY		20

#define			TILECX		64
#define			TILECY		64

#define			OBJ_NOEVENT	 0
#define			OBJ_DEAD	 1

#define			VK_MAX		0xff

enum DIRECTION
{
	DIR_LEFT, 
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LUP,
	DIR_RUP,
	DIR_END
};

enum OBJID
{
	OBJ_PLAYER,
	OBJ_NPC,
	OBJ_BULLET,
	OBJ_EFFECT,
	OBJ_PLAYER_BULLET,
	OBJ_BOOMERANG_BULLET,
	OBJ_SHIELD_REFLECT_BULLET,
	OBJ_OCTOROK_BULLET,
	OBJ_MONSTER_BULLET,
	OBJ_MONSTER,
	OBJ_MOUSE,
	OBJ_SHIELD,
	OBJ_ITEM,
	OBJ_UI,	
	OBJ_BUTTON,
	OBJ_EYE,
	OBJ_OVERRAY_UI,
	OBJ_BOSS,
	OBJ_PORTAL,
	OBJ_END
};

enum RENDERID
{
	RENDER_BACKGROUND,
	RENDER_GAMEOBJECT,
	RENDER_BACKGROUND_HIGH,
	RENDER_EFFECT,
	RENDER_UI_LOW,
	RENDER_UI,
	RENDER_END
};

enum DIRECTION2
{
	LEFT, RIGHT, END
};

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_LINKHOME_STAGE, SC_FIRST_STAGE, SC_VILLAGE_STAGE, SC_PUZZLE_STAGE, SC_CASTLE_STAGE, SC_BOSS_STAGE, SC_FINAL_STAGE, SC_END };

enum CHANNELID {SOUND_PLAYER, SOUND_EFFECT, SOUND_MAPOBJECT, SOUND_GUHU, SOUND_GUHU_EYE, SOUND_BGM,	MAXCHANNEL};


typedef struct tagInfo
{
	float		fX;			// 중점 X
	float		fY;			// 중점 Y
	float		fCX;		// 가로 사이즈
	float		fCY;		// 세로 사이즈

}INFO;

typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef	struct tagLineInfo
{
	LINEPOINT	tLeft;
	LINEPOINT	tRight;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& _tLeft, LINEPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight) { }

}LINEINFO;

typedef struct tagFrame
{
	int		iFrameStart;	// 어디부터 출력할 것인가
	int		iFrameEnd;		// 어디까지 출력할 것인가
	int		iMotion;		// 세로로 증가하는 인덱스
	DWORD	dwSpeed;		// 애니메이션 동작 속도
	DWORD	dwTime;			// 갱신 주기
	DWORD	dwMotionTime;
	tagFrame() { ZeroMemory(this, sizeof(tagFrame)); }
}FRAME;


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct CDeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};
struct CDeleteTerrain
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

typedef struct tagItemInfo
{

	TCHAR* szName;
	TCHAR* szExplain;
	tagItemInfo() : szName(L""), szExplain(L"") 
	{
	}
}ITEM;
extern HWND		g_hWnd;
