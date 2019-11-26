#pragma once
#pragma region Includes
#include "SharedStructs.h"
#pragma endregion //Includes

#define WINDOW_MANAGER_API __declspec(dllexport)

namespace Rendering
{
	namespace Window
	{

		class WINDOW_MANAGER_API WindowManager
		{
		public:

			static HWND CreateNewWindow(const UtilRen::SWindowCreationParams& wndCreationParams, const UtilRen::SWindowClassParams& wndClassParams, const UtilRen::SAdjustWindowRectParams& adjWndRectParams, const UtilRen::SWindowHandleParams& wndHandleParams);
			static void RunWindow(const HWND& wndHandle, MSG& msg);
		};
	}
}