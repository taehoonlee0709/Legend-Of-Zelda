#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CMonster::CMonster()
{
	ZeroMemory(m_tPoint, sizeof(m_tPoint));
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_fSpeed = 3.f;
	m_pFrameKey = L"Monster";
	m_eRender = RENDER_GAMEOBJECT;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Plg.bmp", L"Plg"); 
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Reset.bmp", L"Reset");

}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	float		fDiagonal = sqrt((m_tInfo.fCX / 2.f) * (m_tInfo.fCX / 2.f) + (m_tInfo.fCY / 2.f) * (m_tInfo.fCY / 2.f));

	// 좌상단

	m_tPoint[0].x = LONG(fDiagonal * cosf((m_fAngle + 135.f) * (PI / 180.f)) + (m_tInfo.fCX / 2.f));
	m_tPoint[0].y = LONG(fDiagonal * -sinf((m_fAngle + 135.f) * (PI / 180.f)) + (m_tInfo.fCY / 2.f));
	
	// 우상단
	m_tPoint[1].x = LONG(fDiagonal * cosf((m_fAngle + 45.f) * (PI / 180.f)) + (m_tInfo.fCX / 2.f));
	m_tPoint[1].y = LONG(fDiagonal * -sinf((m_fAngle + 45.f) * (PI / 180.f)) + (m_tInfo.fCY / 2.f));

	// 좌하단
	m_tPoint[2].x = LONG(fDiagonal * cosf((m_fAngle + 225.f) * (PI / 180.f)) + (m_tInfo.fCX / 2.f));
	m_tPoint[2].y = LONG(fDiagonal * -sinf((m_fAngle + 225.f) * (PI / 180.f)) + (m_tInfo.fCY / 2.f));
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (GetAsyncKeyState('A'))
		m_fAngle += 1.f;
}

void CMonster::Render(HDC hDC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hPlgDC = CBmpMgr::Get_Instance()->Find_Image(L"Plg");
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC	hResetDC = CBmpMgr::Get_Instance()->Find_Image(L"Reset");


	PlgBlt(hPlgDC, m_tPoint, hMemDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, NULL, NULL, NULL);
	
	GdiTransparentBlt(hDC,		// (복사 받을)최종적으로 그림을 그릴 DC 전달
		m_tRect.left + iScrollX, // 복사 받을 위치 좌표
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hPlgDC,		// 비트맵을 가지고 있는 DC
		0,			// 비트맵 출력 시작 좌표 LEFT, TOP
		0,
		(int)m_tInfo.fCX,	// 출력할 비트맵 가로
		(int)m_tInfo.fCY,	// 출력할 비트맵 세로
		RGB(255, 255, 255));	// 제거할 색상 값

	BitBlt(hPlgDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hResetDC, 0, 0, SRCCOPY);

}

void CMonster::Release()
{
}
