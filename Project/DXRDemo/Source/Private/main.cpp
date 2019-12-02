#pragma region Includes
#include <windows.h>
#include "SharedMacros.h"
#include "WindowManager.h"
#include "AssetManager.h"
#include "Vulkan.h"
#pragma endregion


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	UtilRen::SWindowCreationParams wndCreationParams = { UtilRen::EResolution::FULL_HD };
	wndCreationParams.HInstance = hInstance;
	wndCreationParams.NCmdShow = nShowCmd;

	UtilRen::SWindowClassParams wndClassParams = {};
	wndClassParams.ClassName = "DXRDemo";

	const UtilRen::SAdjustWindowRectParams adjWndRectParams = {};

	UtilRen::SWindowHandleParams wndHandleParams = {};
	wndHandleParams.ClassName = "DXRDemo";
	wndHandleParams.WindowName = "DXRDemo-MainWindow";

	UtilRen::SWindowParams wndParams = { UtilRen::EResolution::FULL_HD };

	const GUID wndGuid = Rendering::Window::WindowManager::CreateNewWindow(wndCreationParams, wndClassParams, adjWndRectParams, wndHandleParams);
	wndParams.WndHandle = Rendering::Window::WindowManager::GetWindowHandle(wndGuid);
	Rendering::Vulkan::Vulkan vulkanApi = {wndParams.WndHandle, wndParams.WndGuid, hInstance};
	vulkanApi.Init();
	UtAI::AssetManager::Create();
	UtAI::AssetManager* assetManager = UtAI::AssetManager::GetHandle();
	assetManager->Init();
	std::vector<Util::Util::SMesh> meshes = assetManager->GetMeshes();
	std::vector<UtilRen::SVector4> positions = {};
	for (const Util::Util::SMesh& mesh : meshes)
	{
		for (const Util::Util::SVertex& vertex : mesh.Vertices.Vertices)
		{
			UtilRen::SVector4 vector = { vertex.X, vertex.Y, vertex.Z, vertex.W };
			positions.push_back(vector);
		}
	}
	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		Rendering::Window::WindowManager::RunWindow(wndParams.WndHandle, msg);
		vulkanApi.Run();
	}
	vulkanApi.Destroy();
	return static_cast<int>(msg.wParam);
}