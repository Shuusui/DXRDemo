#pragma region Includes
#include <windows.h>
#include "DX12.h"
#include "SharedMacros.h"
#include "WindowManager.h"
#include "SharedStructs.h"
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	UtilRen::SWindowCreationParams wndCreationParams = {UtilRen::EResolution::FULL_HD};
	wndCreationParams.HInstance = hInstance;
	wndCreationParams.NCmdShow = nShowCmd;

	UtilRen::SWindowClassParams wndClassParams = {};
	wndClassParams.ClassName = "DXRDemo";

	UtilRen::SAdjustWindowRectParams adjWndRectParams = {};

	UtilRen::SWindowHandleParams wndHandleParams = {};
	wndHandleParams.ClassName = "DXRDemo";
	wndHandleParams.WindowName = "DXRDemo-MainWindow";

	UtilRen::SWindowParams wndParams = { UtilRen::EResolution::FULL_HD };

	wndParams.WndHandle = Rendering::Window::WindowManager::CreateNewWindow(wndCreationParams, wndClassParams, adjWndRectParams, wndHandleParams);
	
	Rendering::DX12* dx12 = new Rendering::DX12(wndParams); 
	dx12->Init();

	while (Rendering::Window::WindowManager::RunWindow(wndParams.WndHandle) >0)
	{
		dx12->OnRender();
	}
	dx12->OnDestroy();
	delete(dx12);
}