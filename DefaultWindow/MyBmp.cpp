#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : ȣȯ�ϴ� dc�� ����
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,         // ���� �׷��� �ν��Ͻ� �ڵ�
									pFilePath,   // ������ ��� ����
									IMAGE_BITMAP,// � Ÿ������ �о���� �ɼ� ����
									0,			 // �̹��� ���� ������
									0,			 // �̹��� ���� ������
									LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	// LR_LOADFROMFILE : ���Ϸκ��� �̹����� �о���̰ڴٴ� �ɼ�
	// LR_CREATEDIBSECTION : ��ġ�� �������� ��Ʈ�� ���� ���·� ��ȯ�Ͽ� �о����

	// SelectObject : gdi ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
