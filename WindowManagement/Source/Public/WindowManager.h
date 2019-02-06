#pragma once
#pragma region Includes
#include <windows.h>
#include "SharedStructs.h"
#pragma endregion //Includes


namespace Rendering
{
	namespace Window
	{

		class WindowManager
		{
		public:
			static HWND CreateNewWindow(const WindowCreationParams& wndCreationParams, const WindowClassParams& wndClassParams, const AdjustWindowRectParams& adjWndRectParams, const WindowHandleParams& wndHandleParams);
			static int RunWindow(const HWND& wndHandle);
		};
	}
}