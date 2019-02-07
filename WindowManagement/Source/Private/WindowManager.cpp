#include "../Public/WindowManager.h"

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

HWND Rendering::Window::WindowManager::CreateNewWindow(const UtilRen::SWindowCreationParams& wndCreationParams, const UtilRen::SWindowClassParams& wndClassParams, const UtilRen::SAdjustWindowRectParams& adjWndRectParams, const UtilRen::SWindowHandleParams& wndHandleParams)
{
	WNDCLASSEX wndClass = {}; 
	wndClass.cbSize = sizeof(WNDCLASSEX); 
	wndClass.style = wndClassParams.Style;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = wndCreationParams.HInstance; 
	wndClass.lpszClassName = wndClassParams.ClassName; 
	wndClass.hbrBackground = wndClassParams.BackgroundColor; 
	RECT rect = {};
	rect.right = wndCreationParams.Width; 
	rect.bottom = wndCreationParams.Height; 
	AdjustWindowRectEx(&rect, adjWndRectParams.DwStyle, adjWndRectParams.BMenu, adjWndRectParams.DwExStyle); 
	RegisterClassEx(&wndClass); 
	HWND wndHandle = CreateWindowEx(
		wndHandleParams.DwExStyle,
		wndHandleParams.ClassName,
		wndHandleParams.WindowName,
		wndHandleParams.DwStyle,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		wndHandleParams.ParentWindow,
		wndHandleParams.Menu,
		wndCreationParams.HInstance,
		wndHandleParams.LpParam
	);
	ShowWindow(wndHandle, wndCreationParams.NCmdShow);
	UpdateWindow(wndHandle);
	return wndHandle; 
}

int Rendering::Window::WindowManager::RunWindow(const HWND & wndHandle)
{
	MSG msg = {};
	GetMessage(&msg, wndHandle, 0, 0); 
	TranslateMessage(&msg); 
	DispatchMessage(&msg); 
	return (int)msg.wParam;

}
