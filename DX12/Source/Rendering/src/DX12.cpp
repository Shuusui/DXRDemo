#include "..\header\DX12.h"
#include "dxgi1_4.h"
#include "winerror.h"
#include "..\header\DX12Helper.h"

Rendering::DX12::DX12()
{
}

Rendering::DX12::~DX12()
{
}

void Rendering::DX12::Init()
{
	//Enable debuglayer for more debug informations 
#if defined(_DEBUG)
	{
		MSWRL::ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
	}
#endif
	MSWRL::ComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

	MSWRL::ComPtr<IDXGIAdapter> hardwareAdapter;
}
