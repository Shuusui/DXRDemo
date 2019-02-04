#include "..\header\DX12.h"
#include "dxgi1_4.h"
#include "dxgi.h"
#include "winerror.h"
#include "../header/DXSampleHelper.h"

template <typename T>
using WRLComPtr = Microsoft::WRL::ComPtr<T>;

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
		WRLComPtr<ID3D12Debug> debugController; 
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
	}
#endif
	WRLComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));

}
