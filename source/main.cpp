// main.cpp : Defines the entry point for the application.

// Includes:
#include "pch.h"
#include "main.h"

// Entry point function
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_XGPW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Initialise accelerator table
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_XGPW));

	// Initialise msg
	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_XGPW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_XGPW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, winX, winY, nullptr, nullptr, hInstance, nullptr);

	// Find USEDDEFAULT value

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_CREATE		 - Create main window variables
//  WM_SIZE			 - Adjusts window size and position
//  WM_COMMAND		 - process the application menu
//  WM_PAINT		 - Paint the main window
//  WM_GETMINMAXINFO - Handle window size and position
//  WM_DESTROY		 - Destroy window and return
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		// Create window variable
		pWin = new Window(hWnd, hInst, winX, winY, szTitle);
		break;
	}
	case WM_SIZE:
	{
		// Change window position and dimensions
		HWND tc = reinterpret_cast<HWND>(static_cast<LONG_PTR>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
		MoveWindow(tc, 2, 2, LOWORD(lParam) - 4, LOWORD(lParam) - 4, true);
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_OPEN:
		{
			// Open file browser
			pWin->openFile(hWnd);
			break;
		}
		break;

		case IDM_CHOOSE_PATCH:
		{
			// Check for ticked boxes
			pWin->windowSelect();
			break;
		}
		break;

		case IDM_APPLY_PATCH:
		{
			pWin->process();
			break;
		}
		break;

		case IDM_NORMAL:
		{
			pWin->dropdown(pDropDown, "normal");
			break;
		}
		break;

		case IDM_HALF:
		{
			pWin->dropdown(pDropDown, "half");
			break;
		}
		break;

		case IDM_DOUBLE:
		{
			pWin->dropdown(pDropDown, "double");
			break;
		}
		break;

		case IDM_ABOUT:
		{
			// Create "About" dialog
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		}
		break;

		case IDM_EXIT:
		{
			// Close patcher
			pWin->~Window();
			DestroyWindow(hWnd);
			break;
		}
		break;
			
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	// Dropdown menu
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) 
		{
			case BCN_DROPDOWN:
				pDropDown = (NMBCDROPDOWN*)lParam;
				if (pDropDown->hdr.hwndFrom == GetDlgItem(hWnd, 9004) || pDropDown->hdr.hwndFrom == GetDlgItem(hWnd, 9005))
				{
					POINT pt;
					pt.x = pDropDown->rcButton.left;
					pt.y = pDropDown->rcButton.bottom;
					ClientToScreen(pDropDown->hdr.hwndFrom, &pt);

					HMENU hSplitMenu = CreatePopupMenu();
					AppendMenu(hSplitMenu, MF_BYPOSITION, (UINT_PTR)IDM_NORMAL, L"1x");
					AppendMenu(hSplitMenu, MF_BYPOSITION, (UINT_PTR)IDM_HALF, L"1.5x");
					AppendMenu(hSplitMenu, MF_BYPOSITION, (UINT_PTR)IDM_DOUBLE, L"2x");

					TrackPopupMenu(hSplitMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, hWnd, NULL);
				}
				break;
		}
	break;

	case WM_PAINT:
	{
		// Draw window
		pWin->paintProcess();
		break;
	}
	break;

	case WM_GETMINMAXINFO:
	{
		// Update size and position of window
		minMaxInfo(lParam);
		break;
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

// Update size and position of window
void minMaxInfo(LPARAM lParam) {
	LPMINMAXINFO pMMI = (LPMINMAXINFO)lParam;
	pMMI->ptMaxTrackSize.x = winX;
	pMMI->ptMaxTrackSize.y = winY;
}