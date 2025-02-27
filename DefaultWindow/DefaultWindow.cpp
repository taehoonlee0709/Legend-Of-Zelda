// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// â �ܰ����� ��Ÿ�� ���� �Լ�
BOOL                InitInstance(HINSTANCE, int);			// â ������ ���õ� �Լ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// ������ �޼��� ó�� �Լ�
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// ���� â ��� �Լ�

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// ���� ���α׷��� ���� �ĺ� ��ȣ : �޸� �Ҵ�Ǵ� ��ü, �� ��ü, api���� ���� �����ǰ� �ִ� ���α׷� �ν��Ͻ�(���� ����ǰ� �ִ� ���α׷� �޸�)
                     _In_opt_ HINSTANCE hPrevInstance,		// ���� ����Ǿ��� �ν��Ͻ��� �ڵ�, ���� ��� NULL
                     _In_ LPWSTR    lpCmdLine,				// ���ڿ�(��)
                     _In_ int       nCmdShow)				// ������ â�� ��Ÿ��(��� / �ּ�ȭ �Ǵ� �ִ�ȭ ���) �ɼ�
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
  
	MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;
	msg.message = WM_NULL;	

	CMainGame		MainGame;

	MainGame.Initialize();

	DWORD	dwTime = GetTickCount();	// 100

    while (true)
    {
		// PM_REMOVE   : �޼����� �о�Ȱ� ���ÿ� �޼��� ť���� ����
		// PM_NOREMOVE : �޼��� ť�� �޼����� �����ϴ����� �ľ�, �޼����� �о���̷��� GetMessage�� �ٽ� ȣ��

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// TranslateAccelerator : �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// TranslateMessage : Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
				TranslateMessage(&msg);

				//DispatchMessage : �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó�� �Լ�(WndProc)�� �����ϴ� �Լ�
				DispatchMessage(&msg);
			}
		}
		else
		{		
			if (dwTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				dwTime = GetTickCount();
			}

		/*	MainGame.Update();
			MainGame.Late_Update();
			MainGame.Render();*/
		}
		
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;		// ������ â�� ���� Ư���� �����ϱ� ���� ����ü

    wcex.cbSize = sizeof(WNDCLASSEX);	// â ����� ����

    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// ���� | ���θ� �ٽ� �׸���(������ â�� ���� �Ǵ� ������ ũ�Ⱑ ���� ��� ������ â�� �ٽ� �׸��ٴ� �ɼ�)
    wcex.lpfnWndProc    = WndProc;	// �����ص� �Լ��� ȣ��Ǿ� �޽����� ó���ϵ��� ��
    
	wcex.cbClsExtra     = 0;	// �����찡 Ư���� �������� ����ϴ� ������ ����
    wcex.cbWndExtra     = 0;	// ������ ���� �����̸� ������� ���� ��� 0���� ����
    
	wcex.hInstance      = hInstance;	// ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ�� ����

    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
						 // ������ â�� ����� �������� ����(���� ǥ����)

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
						// ������ â���� ����� ���콺 Ŀ���� ����� ����

    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
						// ������ �۾� ������ ��� ���� ����

	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
						// â ��ܿ� �ִ� �޴� ����

    wcex.lpszClassName  = szWindowClass;
						// ���������� �̸��� ����, �������̸� ������Ʈ �̸��� ��ġ
		
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
						// â ��ܿ� �ִ� ���� ������ ����� ����

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT	rc{ 0, 0, WINCX,WINCY };

   // rc = rc + �⺻ ������ â ��Ÿ�� + �޴� ���� ũ�� ���
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   
   // CreateWindowW : ����� ���� �������� ���� â�� �����ϴ� �Լ�
   HWND hWnd = CreateWindowW(szWindowClass,		  // �ռ� ������ ������ Ŭ���� ������ Ŭ���� �̸�
							 szTitle,			  // ������ ����� ��Ÿ�� ���ڿ�
							 WS_OVERLAPPEDWINDOW, // ������� �ϴ� ������ ��Ÿ�� ���� : �⺻ ������ ����ϴ� ���
							 CW_USEDEFAULT, 0,	  // �����ϴ� â�� X,Y ��ġ
							 rc.right - rc.left, 
							 rc.bottom - rc.top,	  // �����ϴ� â�� ����, ���� ������
							 nullptr,	  // �θ� ������ �ڵ�. ���� ��� NULL
							 nullptr,	  // �����쿡�� ����� �޴� �ڵ�, �������Ϳ� ��ϵ� �޴� ���¸� ����Ϸ��� NULL
 							 hInstance,	  // �����츦 ����� ��ü, ���α׷� �ڵ��� ����	
							 nullptr);	  // �ü���� Ư���� �������� ���

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// ���̺귯�� : ���̳ʸ��� ����(������)�� �Լ����� ��Ƴ��� ����

// - �ڵ� ������ ���� ��â�� ��� �� �ϳ��̸�, �ٸ� ���α׷����� ����� �� �ֵ��� �ü���� ����Ʈ���� �����ڿ� ���� ����

// - ���̺귯���� ��ټ� �Լ����� �Լ��� ���� �� ������� �ʿ�� �ϱ� ������ ��ũ �Ǳ� ��, ��ó���⿡ ���� �ش� ���������
// ���� ���α׷��� ���Խ��Ѿ� �Ѵ�.

// - ���̺귯������ ������� ���α׷��� ��ũ�Ǿ� ������ ������ ������ ���α׷��� �̷�� �ȴ�.

// kernel : �޸𸮸� �����ϰ� ���α׷��� �����Ű�� ����
// user : ���� �������̽��� ������ ���� ����
// gdi : ȭ�� ó���� �׷��� ���

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;   

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;		
		}
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// �Լ� ȣ�� �Ծ� 

// - �Լ��� ������ ����Ǹ� �Ҵ� �Ǿ��� stack�� �Ҹ���Ѿ� �ϴµ� �̶� �Լ��� ȣ���� ȣ������� ������ �� �ƴϸ� ȣ�� ���� �� ȣ���ڿ��� �� �������� ���� ���

// __cdecl : c / c++ ����� �⺻ ȣ�� �Ծ�, ȣ����� stack�� ����, �������� �Լ�(�Ű� ������ �󸶳� ��� ���� �� �𸥴�)

// __stdcall : win32 api�� �⺻ ȣ�� �Ծ�, ��ȣ���ڰ� stack�� ����, �������� �Լ�(�Ű� ������ �̹� ���� �Ǿ�����)

// __fastcall : �Լ� ȣ���� ������ ó���ϱ� ���� ȣ�� �Ծ�, ecx�� edx��� �������͸� ���� ����, �������͸� ����ϰ� �ִٴ� ������ �Լ� ȣ���� �������� �ٰŰ� ��

// __thiscall : this �����͸� �Ű� ������ ���� �� ����ϴ� ȣ�� �Ծ�


// 1. �׸��� �׷��Ͷ�
// 2. W,A,S,D Ű �������� �Ѿ��� �������� ������, SPACE ������ �� �������� �������� ����

