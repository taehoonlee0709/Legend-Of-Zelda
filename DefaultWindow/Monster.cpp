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

	// �»��

	m_tPoint[0].x = LONG(fDiagonal * cosf((m_fAngle + 135.f) * (PI / 180.f)) + (m_tInfo.fCX / 2.f));
	m_tPoint[0].y = LONG(fDiagonal * -sinf((m_fAngle + 135.f) * (PI / 180.f)) + (m_tInfo.fCY / 2.f));
	
	// ����
	m_tPoint[1].x = LONG(fDiagonal * cosf((m_fAngle + 45.f) * (PI / 180.f)) + (m_tInfo.fCX / 2.f));
	m_tPoint[1].y = LONG(fDiagonal * -sinf((m_fAngle + 45.f) * (PI / 180.f)) + (m_tInfo.fCY / 2.f));

	// ���ϴ�
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
	
	GdiTransparentBlt(hDC,		// (���� ����)���������� �׸��� �׸� DC ����
		m_tRect.left + iScrollX, // ���� ���� ��ġ ��ǥ
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// ���� ���� �̹����� ����, ����
		(int)m_tInfo.fCY,
		hPlgDC,		// ��Ʈ���� ������ �ִ� DC
		0,			// ��Ʈ�� ��� ���� ��ǥ LEFT, TOP
		0,
		(int)m_tInfo.fCX,	// ����� ��Ʈ�� ����
		(int)m_tInfo.fCY,	// ����� ��Ʈ�� ����
		RGB(255, 255, 255));	// ������ ���� ��

	BitBlt(hPlgDC, 0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, hResetDC, 0, 0, SRCCOPY);

}

void CMonster::Release()
{
}
