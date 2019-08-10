#pragma region Includes
#include <windows.h>
#include "DX12.h"
#include "SharedMacros.h"
#include "WindowManager.h"
#include "SharedStructs.h"
#include "AssetManager.h"
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

	wndParams.WndHandle = Rendering::Window::WindowManager::CreateNewWindow(wndCreationParams, wndClassParams, adjWndRectParams, wndHandleParams);

	Rendering::DX12* dx12 = new Rendering::DX12(wndParams);
	dx12->Init();

	UtAI::MLAssetManager::Create();
	UtAI::MLAssetManager* assetManager = UtAI::MLAssetManager::GetHandle();
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
	dx12->LoadAssets(positions);
	dx12->LoadShader(assetManager->GetShaderPaths());
	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		Rendering::Window::WindowManager::RunWindow(wndParams.WndHandle, msg);
		dx12->OnRender();
	}
	dx12->OnDestroy();
	delete(dx12);
	return static_cast<int>(msg.wParam);
}