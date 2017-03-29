#include <windows.h>
#include <string>
#undef UNICODE
#include "Field.h"
using namespace std;

BOOL InitApplication(HINSTANCE hinstance);
BOOL InitInstance(HINSTANCE hinstance, int nCMdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT messagem, WPARAM wparam, LPARAM lparam);

void DrawCircle(HDC &hdc, RECT& square);
void DrawCross(HDC &hdc, RECT& square);

static unsigned int cellNumber = 3;
static HWND procHWND;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	InitApplication(hInstance);
	// after application initialization I should create dialog window to 
	// make user input number of cells per raw
	// that variables will be global

	InitInstance(hInstance, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static Field field;

	static HDC hdc;
	static int x, y;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		RECT clientArea;
		GetClientRect(hwnd, &clientArea);
		field = Field(clientArea.right, clientArea.bottom, cellNumber);
		break;
	case  WM_SIZE:
	{
		// Updating window dimension in pixels after resizing
		RECT clientArea;
		GetClientRect(hwnd, &clientArea);
		x = clientArea.right; y = clientArea.bottom;
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		field.prepareBackground(hdc);
		EndPaint(hwnd, &ps);
	}
		break;
	case  WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return FALSE;
}

BOOL InitApplication(HINSTANCE hinstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hinstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = (LPSTR)"Gomoku";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Unable to init app", "Error", MB_OK);
		return FALSE;
	}
	return TRUE;
}
BOOL InitInstance(HINSTANCE hinstance, int nCMdShow)
{
	procHWND = CreateWindow(
		"Gomoku",
		"Gomoku",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0,
		0,
		700,
		700,
		NULL,
		NULL,
		hinstance,
		NULL
	);

	if (!procHWND)
	{
		MessageBox(NULL, "Cannot init instance", "Error", MB_OK);
		return FALSE;
	}

	ShowWindow(procHWND, nCMdShow);
	UpdateWindow(procHWND);
	return TRUE;
}
