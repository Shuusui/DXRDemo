#pragma region Includes
#include <windows.h>
#include "DX12.h"
#include "SharedMacros.h"
#include "WindowManager.h"
#include "SharedStructs.h"
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	UtilRen::SWindowCreationParams wndCreationParams = { UtilRen::EResolution::FULL_HD };
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

<<<<<<< Updated upstream
	UtAI::AssetManager* assetManager = new UtAI::AssetManager();
	assetManager->Init();
	assetManager->ImportAsset("shaders.hlsl");
=======
	UtAI::AssetManager::Create();
	UtAI::AssetManager* assetManager = UtAI::AssetManager::GetHandle();
	assetManager->Init();
	dx12->LoadShader(assetManager->GetShaderPaths());
>>>>>>> Stashed changes

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		dx12->OnRender();
		Rendering::Window::WindowManager::RunWindow(wndParams.WndHandle, msg);
	}
	dx12->OnDestroy();
	delete(dx12);
<<<<<<< Updated upstream
	return msg.wParam;
=======
	return static_cast<int>(msg.wParam);
>>>>>>> Stashed changes
}