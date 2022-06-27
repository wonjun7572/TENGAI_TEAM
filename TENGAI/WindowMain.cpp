// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "pch.h"
#include "Resource.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

HWND	g_hWnd;

RECT	g_WindowRect = { 0,0,WINCX,WINCY };
RECT	g_WindowRect_MonsterHouse = { 0,0,WINCX + 100,WINCY};

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// â ��Ÿ���� �����ϱ� ���� �Լ�
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// �޸𸮿� �Ҵ�Ǵ� ��ü. �� ��ü, api������ ���� �����ǰ� �ִ� ���α׷��� �ǹ�
	_In_opt_ HINSTANCE hPrevInstance,	// ���� ����Ǿ��� �ν��Ͻ��� �ڵ��� ���� ��, ���� ��� �ڵ����� NULL������ ä����
	_In_ LPWSTR    lpCmdLine,			// ���ڿ� �����͸� �ǹ�
	_In_ int       nCmdShow)			// â ��¿� ���� ����Ű ���

{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TENGAI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TENGAI));

	MSG msg;
	msg.message = WM_NULL;


	// GetTickCount() : �ü���� �����ϸ� ���������� �帥 �ð��� ���� ���·� ��ȯ
	// 1�ʶ�� �ð��� ���� �뷫 1000���� ���� �������� ���� �Ǵ�

	//		1000
	DWORD	dwOldTime = GetTickCount();

	
	CMainGame		MainGame;
	MainGame.Initialize();

	// �⺻ �޽��� �����Դϴ�.
	while (true)
	{
		//	PeekMessage : �޼����� �о���� true, �޼����� ���ٸ� false�� ��ȯ

		// PM_REMOVE : �޼����� �޼��� ť�κ��� �о�Ȱ� ���ÿ� �޼��� ť���� ����
		// PM_NOREMOVE : �޼��� ť�� �޼����� �ִ��� ���縸 �ľ�
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			// �޴� ����� ����Ű�� ����� �۵��ϴ��� �˻��ϴ� �Լ�
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
				TranslateMessage(&msg);

				// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �޼��� ó��(wndproc)�Լ��� �����ϴ� �Լ�
				DispatchMessage(&msg);
			}
		}

		else
		{
			// 1020 + 10     1011
			if (dwOldTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.LateUpdate();
				MainGame.Render();

				// 1020
				dwOldTime = GetTickCount();
			}
		}
	}

	return (int)msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TENGAI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	RECT	rc{ 0, 0, WINCX, WINCY };


	// rc = rcũ�� + �⺻ â ��Ÿ�� + �޴� �� ������ ��� ����
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		400, 200,		// ������ â�� ����� ��ġ
		rc.right - rc.left, rc.bottom - rc.top,		// ������ â�� ����, ���� ������
		nullptr, nullptr, hInstance, nullptr);

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
			break;
		case IDM_EXIT:
			DestroyWindow(g_hWnd);
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

