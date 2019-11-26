#include "../Public/WindowManager.h"
//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
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
	rect.right = wndCreationParams.WIDTH; 
	rect.bottom = wndCreationParams.HEIGHT; 
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

void Rendering::Window::WindowManager::RunWindow(const HWND & wndHandle, MSG& msg)
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}
