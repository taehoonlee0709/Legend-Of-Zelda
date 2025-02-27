#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "SoundMgr.h"



CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/MenuBack1.bmp", L"MenuBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/MenuPlayer.bmp", L"MenuPlayer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");

	//���� �߰�
	CSoundMgr::Get_Instance()->PlayBGM(L"Menu.wav", 1.f);

	CObj* pButton = CAbstractFactory<CMyButton>::Create(150.f, 500.f);
	pButton->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(400.f, 500.f);
	pButton->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);

	pButton = CAbstractFactory<CMyButton>::Create(650.f, 500.f);
	pButton->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(OBJ_BUTTON, pButton);


}

int CMyMenu::Update()
{
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MenuBack");
	HDC	hPlayerDC = CBmpMgr::Get_Instance()->Find_Image(L"MenuPlayer");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	int iStartPoint = (GetTickCount() % 1000) / 100;

	GdiTransparentBlt(hDC,
		150, // ���� ���� ��ġ x, y ��ǥ
		200,
		100,	// ���� ���� ����, ���� ����
		100,
		hPlayerDC,		// ������ �̹��� dc
		100 * iStartPoint,
		0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		100,	// ������ �̹����� ����, ���� ������
		100,
		RGB(128, 128, 128));	// �����ϰ��� �ϴ� ����

}

void CMyMenu::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);

}
