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
		struct SHARED_STRUCTS_API SVector4
		{
			float X;
			float Y;
			float Z;
			float W;

			SVector4() = default;

			SVector4(const SVector4& other) = default;

			SVector4(const float& x, const float& y, const float& z, const float& w = 1.0f)
				:X(x)
				,Y(y)
				,Z(z)
				,W(w)
			{

			}

			~SVector4() = default;
		}; 

		struct SHARED_STRUCTS_API SVertex
		{
			SVector4 Position;
			SVector4 Color;
		};

		struct SHARED_STRUCTS_API SWindowParams
		{
			SWindowParams(const EResolution& res)
				:WIDTH(GetResolution(res).WIDTH)
				,HEIGHT(GetResolution(res).HEIGHT)
				,WndGuid({})
			{

			}
			HWND WndHandle = {};
			const unsigned short WIDTH;
			const unsigned short HEIGHT;
			const GUID WndGuid;
		};
		struct SHARED_STRUCTS_API SWindowCreationParams
		{
			SWindowCreationParams(const EResolution& res)
				:WIDTH(GetResolution(res).WIDTH)
				,HEIGHT(GetResolution(res).HEIGHT)
				,NCmdShow(-1)
			{

			}
			const unsigned short WIDTH;
			const unsigned short HEIGHT;
			HINSTANCE HInstance = {};
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