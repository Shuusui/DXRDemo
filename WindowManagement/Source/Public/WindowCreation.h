#pragma once
#pragma region Includes
#include <windows.h>
#pragma endregion //Includes


namespace Window
{
	class WindowCreation
	{
	public:
		static HWND CreateNewWindow(unsigned short width, unsigned short height, HINSTANCE hInstance, int nCmdShow);
	};
}