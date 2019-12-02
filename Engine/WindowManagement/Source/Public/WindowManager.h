#pragma once
#pragma region Includes
#include "SharedStructs.h"
#include <functional>

#pragma endregion //Includes

#define WINDOW_MANAGER_API __declspec(dllexport)

namespace Rendering
{
	namespace Window
	{
		struct WINDOW_MANAGER_API WindowInformation
		{
			HWND WndHandle;
			void* UserPtr;

			FORCEINLINE bool operator==(const HWND& OtherWndHandle) const
			{
				return WndHandle == OtherWndHandle;
			}
			FORCEINLINE bool operator!=(const HWND& OtherWndHandle) const
			{
				return WndHandle != OtherWndHandle;
			}
		};

		class WINDOW_MANAGER_API WindowManager
		{
		public:
			static GUID CreateNewWindow(const UtilRen::SWindowCreationParams& wndCreationParams, const UtilRen::SWindowClassParams& wndClassParams, const UtilRen::SAdjustWindowRectParams& adjWndRectParams, const UtilRen::SWindowHandleParams& wndHandleParams);
			static void RunWindow(const HWND& wndHandle, MSG& msg);
			static HWND GetWindowHandle(const GUID& wndGuid);
			static void SetFramebufferSizeCallback(std::function<void(HWND, int32_t, int32_t)> func);
			static void SetWindowUserPtr(const GUID& guid, void* userPtr);
			static void* GetWindowUserPtr(const GUID& guid);
		};
	}
}