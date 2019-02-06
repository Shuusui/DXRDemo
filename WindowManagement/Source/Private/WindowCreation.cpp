#include "../Public/WindowCreation.h"

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	if (message == WM_CLOSE)
	{
		PostQuitMessage(0);
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

HWND Window::WindowCreation::CreateNewWindow(unsigned short width, unsigned short height, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wndClass = {}; 
	wndClass.cbSize = sizeof(WNDCLASSEX); 
	wndClass.style = CS_HREDRAW | CS_VREDRAW; 
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = hInstance; 
	wndClass.lpszClassName = "Window"; 
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW; 
	RECT rect = {};
	rect.right = width; 
	rect.bottom = height; 
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, 0); 
	RegisterClassEx(&wndClass); 
	HWND wndHandle = CreateWindowEx(
		NULL,
		"Window",
		"DXRDemo",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
	return wndHandle; 
}
