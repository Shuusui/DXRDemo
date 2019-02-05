#include "..\header\DX12.h"
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

	MSWRL::ComPtr<IDXGIAdapter1> hardwareAdapter;

	GetHardwareAdapter(factory.Get(), &hardwareAdapter); 
	ThrowIfFailed(D3D12CreateDevice(
		hardwareAdapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m_device)
	));

	D3D12_COMMAND_QUEUE_DESC queueDesc = {}; 
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; 
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; 

	ThrowIfFailed(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue))); 

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {}; 
	swapChainDesc.BufferCount = FrameCount; 
	swapChainDesc.BufferDesc.Width = 1920; 
	swapChainDesc.BufferDesc.Height = 1080; 
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; 
	swapChainDesc.OutputWindow; //TODO: Add output window here
	swapChainDesc.SampleDesc.Count = 1; 
	swapChainDesc.Windowed = FALSE; 

	MSWRL::ComPtr<IDXGISwapChain> swapChain; 
	ThrowIfFailed(
		factory->CreateSwapChain(m_commandQueue.Get(), 
			&swapChainDesc, 
			&swapChain
		)); 
	ThrowIfFailed(swapChain.As(&m_swapChain));

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {}; 
		rtvHeapDesc.NumDescriptors = FrameCount; 
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; 
		ThrowIfFailed(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap))); 

		m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
	
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

		for (UINT n = 0; n < FrameCount; n++)
		{
			ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
			m_device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
			rtvHandle.Offset(1, m_rtvDescriptorSize);
		}

	}
	ThrowIfFailed(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));


}
