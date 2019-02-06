#pragma once
#pragma region Includes
#include <windows.h>
#pragma endregion

#define SHARED_STRUCTS_API __declspec(dllexport)

namespace Rendering
{
	struct SHARED_STRUCTS_API WindowParams
	{
		HWND WndHandle; 
		const unsigned short Width; 
		const unsigned short Height;
	};
	struct SHARED_STRUCTS_API WindowCreationParams
	{
		const unsigned short Width;
		const unsigned short Height;
		HINSTANCE HInstance;
		const int NCmdShow;
	};
	struct SHARED_STRUCTS_API  WindowClassParams
	{
		UINT Style = CS_HREDRAW | CS_VREDRAW;
		LPCSTR ClassName = "";
		HBRUSH BackgroundColor = HBRUSH(COLOR_WINDOW);
	};
	struct SHARED_STRUCTS_API AdjustWindowRectParams
	{
		DWORD DwStyle = WS_OVERLAPPEDWINDOW;
		BOOL BMenu = FALSE;
		DWORD DwExStyle = NULL;
	};
	struct SHARED_STRUCTS_API WindowHandleParams
	{
		DWORD DwExStyle = NULL;
		LPCSTR ClassName = "";
		LPCSTR WindowName = "";
		DWORD DwStyle = WS_OVERLAPPEDWINDOW;
		HWND ParentWindow = nullptr;
		HMENU Menu = nullptr;
		LPVOID LpParam = nullptr;
	};
}