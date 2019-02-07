#pragma once
#pragma region Includes
#include <windows.h>
#include "SharedMacros.h"
#include "HelperFunctions.h"
#pragma endregion

#define SHARED_STRUCTS_API __declspec(dllexport)
namespace Util
{
	namespace Rendering
	{
		struct SHARED_STRUCTS_API SWindowParams
		{
			SWindowParams(const EResolution& res)
				:Width(GetResolution(res).Width)
				,Height(GetResolution(res).Height)
			{

			}
			HWND WndHandle;
			const unsigned short Width;
			const unsigned short Height;
		};
		struct SHARED_STRUCTS_API SWindowCreationParams
		{
			SWindowCreationParams(const EResolution& res)
				:Width(GetResolution(res).Width)
				,Height(GetResolution(res).Height)
			{

			}
			const unsigned short Width;
			const unsigned short Height;
			HINSTANCE HInstance;
			int NCmdShow;
		};
		struct SHARED_STRUCTS_API  SWindowClassParams
		{
			UINT Style = CS_HREDRAW | CS_VREDRAW;
			LPCSTR ClassName = "";
			HBRUSH BackgroundColor = HBRUSH(COLOR_WINDOW);
		};
		struct SHARED_STRUCTS_API SAdjustWindowRectParams
		{
			DWORD DwStyle = WS_OVERLAPPEDWINDOW;
			BOOL BMenu = FALSE;
			DWORD DwExStyle = NULL;
		};
		struct SHARED_STRUCTS_API SWindowHandleParams
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
}