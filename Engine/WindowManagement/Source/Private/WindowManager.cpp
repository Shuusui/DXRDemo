#include "../Public/WindowManager.h"
#include <utility>
#include <map>

static std::function<void(HWND, int32_t, int32_t)> s_framebufferSizeCallback;
static std::map<GUID, Rendering::Window::WindowInformation> s_WindowsMap;

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
	case WM_EXITSIZEMOVE:
		RECT rect = {};
		GetWindowRect(hwnd, &rect);
		s_framebufferSizeCallback(hwnd, rect.right-rect.left, rect.bottom-rect.top);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}

GUID Rendering::Window::WindowManager::CreateNewWindow(const UtilRen::SWindowCreationParams& wndCreationParams, const UtilRen::SWindowClassParams& wndClassParams, const UtilRen::SAdjustWindowRectParams& adjWndRectParams, const UtilRen::SWindowHandleParams& wndHandleParams)
{
	Rendering::Window::WindowInformation ReturnInfo = {};
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
	ReturnInfo.WndHandle = CreateWindowEx(
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
	ShowWindow(ReturnInfo.WndHandle, wndCreationParams.NCmdShow);
	UpdateWindow(ReturnInfo.WndHandle);

	GUID wndGuid = {};
	if(CoCreateGuid(&wndGuid) != S_OK)
	{
		return wndGuid;
	}
	s_WindowsMap.insert(std::make_pair(wndGuid, ReturnInfo));

	return wndGuid;
}

void Rendering::Window::WindowManager::RunWindow(const HWND & wndHandle, MSG& msg)
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

HWND Rendering::Window::WindowManager::GetWindowHandle(const GUID& wndGuid)
{
	return s_WindowsMap.at(wndGuid).WndHandle;
}

void Rendering::Window::WindowManager::SetFramebufferSizeCallback(std::function<void(HWND, int32_t, int32_t)> func)
{
	s_framebufferSizeCallback = std::move(func);
}

void Rendering::Window::WindowManager::SetWindowUserPtr(const GUID& guid, void* userPtr)
{
	s_WindowsMap.at(guid).UserPtr = userPtr;
}

void* Rendering::Window::WindowManager::GetWindowUserPtr(const GUID& guid)
{
	return s_WindowsMap.at(guid).UserPtr;
}
