#include "..\Public\DX12.h"
#include "..\Public\DX12Helper.h"
#include "winerror.h"
//#if defined (_DEBUG)
#include "D3DCompiler.h"
//#endif

Rendering::DX12::DX12(const UtilRen::SWindowParams& wndParams)
	:m_wndParams(wndParams)
	, m_viewport(0.0f, 0.0f, static_cast<float>(wndParams.WIDTH), static_cast<float>(wndParams.HEIGHT))
	, m_scissorRect(0, 0, static_cast<LONG>(wndParams.WIDTH), static_cast<LONG>(wndParams.HEIGHT))
	, m_aspectRatio(static_cast<float>(wndParams.WIDTH) / static_cast<float>(wndParams.HEIGHT))
	, m_rtvDescriptorSize(0)
	, m_vertexBufferView(D3D12_VERTEX_BUFFER_VIEW{})
	, m_frameIndex(0)
	, m_fenceEvent(nullptr)
	, m_fenceValue(0)
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
	swapChainDesc.BufferDesc.Width = m_wndParams.WIDTH;
	swapChainDesc.BufferDesc.Height = m_wndParams.HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; 
	swapChainDesc.OutputWindow = m_wndParams.WndHandle;
	swapChainDesc.SampleDesc.Count = 1; 
	swapChainDesc.Windowed = TRUE;

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

void Rendering::DX12::OnRender()
{
	PopulateCommandList(); 

	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists); 

	//Present the frame
	ThrowIfFailed(m_swapChain->Present(1, 0)); 

	WaitForPreviousFrame();
}

void Rendering::DX12::PopulateCommandList()
{
	ThrowIfFailed(m_commandAllocator->Reset());

	ThrowIfFailed(m_commandList->Reset(m_commandAllocator.Get(), m_pipelineState.Get()));

	m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());
	m_commandList->RSSetViewports(1, &m_viewport);
	m_commandList->RSSetScissorRects(1, &m_scissorRect);

	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, m_rtvDescriptorSize);
	m_commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	const float clearColor[] = { 0.0f, 0.2f, 0.4f,1.0f };
	m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	m_commandList->DrawInstanced(3, 1, 0, 0);

	m_commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	ThrowIfFailed(m_commandList->Close());
}

void Rendering::DX12::WaitForPreviousFrame()
{
	const UINT64 fence = m_fenceValue; 
	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), fence)); 
	m_fenceValue++; 

	if (m_fence->GetCompletedValue() < fence)
	{
		ThrowIfFailed(m_fence->SetEventOnCompletion(fence, m_fenceEvent));
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}
	
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

}

void Rendering::DX12::LoadAssets(const std::vector<UtilRen::SVector4>& vertexPos)
{
	for (const UtilRen::SVector4& pos : vertexPos)
	{
		UtilRen::SVertex vertex = {};
		vertex.Position = pos;
		vertex.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_vertices.push_back(vertex);
	}
}

void Rendering::DX12::OnDestroy()
{
	WaitForPreviousFrame(); 

	CloseHandle(m_fenceEvent);
}

void Rendering::DX12::LoadShader(const std::vector<std::wstring>& shaderPaths)
{
	{
		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		MSWRL::ComPtr<ID3DBlob> signature;
		MSWRL::ComPtr<ID3DBlob> error;
		ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		ThrowIfFailed(m_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
	}
	{
		MSWRL::ComPtr<ID3DBlob> vertexShader;
		MSWRL::ComPtr<ID3DBlob> pixelShader;

#if defined (_DEBUG)
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif 
		for (const std::wstring& shaderPath : shaderPaths)
		{
			ThrowIfFailed(D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr)); 
			ThrowIfFailed(D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));
		}

		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
			{"Color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
		};

		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = m_rootSignature.Get();
		psoDesc.VS = { reinterpret_cast<UINT8*>(vertexShader->GetBufferPointer()), vertexShader->GetBufferSize() };
		psoDesc.PS = { reinterpret_cast<UINT8*>(pixelShader->GetBufferPointer()), pixelShader->GetBufferSize() };
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		ThrowIfFailed(m_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)));
	}

	ThrowIfFailed(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), m_pipelineState.Get(), IID_PPV_ARGS(&m_commandList)));

	ThrowIfFailed(m_commandList->Close());

	{
		//UtilRen::SVertex triangleVertices[] =
		//{
		//	{{0.0f, 0.25f * m_aspectRatio, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
		//	{{0.25f, -0.25f * m_aspectRatio, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
		//	{{-0.25f, -0.25f * m_aspectRatio, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
		//};
		const UINT vertexBufferSize = m_vertices.size();

		ThrowIfFailed(m_device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)));

		UINT8* pVertexDataBegin = nullptr;
		CD3DX12_RANGE readRange(0, 0);

		ThrowIfFailed(m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, m_vertices.data(), m_vertices.size());
		m_vertexBuffer->Unmap(0, nullptr);

		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.StrideInBytes = sizeof(UtilRen::SVertex);
		m_vertexBufferView.SizeInBytes = vertexBufferSize;
	}
	{
		ThrowIfFailed(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
		m_fenceValue = 1;

		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (m_fenceEvent == nullptr)
		{
			ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		}
		WaitForPreviousFrame();
	}
}