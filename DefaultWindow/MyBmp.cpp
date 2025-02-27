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

	// CreateCompatibleDC : 호환하는 dc를 복사
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL,         // 프로 그램의 인스턴스 핸들
									pFilePath,   // 파일의 경로 전달
									IMAGE_BITMAP,// 어떤 타입으로 읽어올지 옵션 설정
									0,			 // 이미지 가로 사이즈
									0,			 // 이미지 세로 사이즈
									LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	// LR_LOADFROMFILE : 파일로부터 이미지를 읽어들이겠다는 옵션
	// LR_CREATEDIBSECTION : 장치에 독립적인 비트맵 포맷 형태로 전환하여 읽어들임

	// SelectObject : gdi 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}
