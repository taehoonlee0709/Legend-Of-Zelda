#include "stdafx.h"
#include "TextBoxMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"

CTextBoxMgr* CTextBoxMgr::m_pInstance = nullptr;

CTextBoxMgr::CTextBoxMgr() : m_bIsTextBoxON(false), m_szText(L"")
{
}

CTextBoxMgr::~CTextBoxMgr()
{
}

void CTextBoxMgr::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/TextBox.bmp", L"TextBox");
	m_szText = L"���";
}

int CTextBoxMgr::Update()
{
	//m_bIsTextBoxON = true;
	Key_Input();
	return 0;
}

void CTextBoxMgr::Late_Update()
{
}

void CTextBoxMgr::Render(HDC hDC)
{
	if (false == m_bIsTextBoxON)
		return;
	/////
	//HBRUSH MyBrush, OldBrush;
	HFONT hFont, OldFont;

	//MyBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
	//OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
	//SelectObject(hDC, OldBrush);
	hFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, L"����");
	OldFont = (HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkMode(hDC, TRANSPARENT);

	/////////////////
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TextBox");

	GdiTransparentBlt(hDC,
		(int)TEXTBOX_LEFT, // ���� ���� ��ġ x, y ��ǥ
		TEXTBOX_TOP,
		TEXTBOX_CX,	// ���� ���� ����, ���� ����
		TEXTBOX_CY,
		hMemDC,		// ������ �̹��� dc
		0,
		0,		// ��Ʈ�� �̹��� ��� ���� ��ǥ
		TEXTBOX_CX,	// ������ �̹����� ����, ���� ������
		TEXTBOX_CY,
		RGB(255, 255, 255));	// �����ϰ��� �ϴ� ����
	RECT rcTextBox = { (int)TEXTBOX_LEFT + 24 ,TEXTBOX_TOP + 24 , (int)TEXTBOX_RIGHT - 24, TEXTBOX_BOTTOM - 24 };

	DrawText(hDC, m_szText, lstrlen(m_szText), &rcTextBox, DT_LEFT | DT_WORDBREAK);

	//TextOut(hDC, (int)TEXTBOX_LEFT + 24, TEXTBOX_TOP + 24, m_szText, lstrlen(m_szText));

	SelectObject(hDC, OldFont);
	//DeleteObject(MyBrush);
	DeleteObject(hFont);

}

void CTextBoxMgr::Release()
{
}

void CTextBoxMgr::Set_IsTextBoxON()
{
	if (true == m_bIsTextBoxON)
		m_szText = L"";
	m_bIsTextBoxON = !m_bIsTextBoxON;
}

void CTextBoxMgr::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('T'))
	{
		Set_IsTextBoxON();
	}
}
