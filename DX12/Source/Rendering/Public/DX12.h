#pragma once

#pragma region Includes
#include "d3dx12.h"
#include "dxgi.h"
#include "dxgi1_4.h"
#include "directxmath.h"
#include "SharedStructs.h"
#pragma endregion

#define DX12_API __declspec(dllexport)

namespace Rendering
{
	namespace MSWRL = Microsoft::WRL; 
	class DX12_API DX12
	{
	public:
		DX12() = delete; 
		DX12(const UtilRen::SWindowParams& wndCreationParams);
		~DX12();
		void Init();
		void OnRender();
		void OnDestroy();
	private: 
		UtilRen::SWindowParams m_wndParams;

		struct SVertex
		{
			DirectX::XMFLOAT3 position; 
			DirectX::XMFLOAT4 color; 
		};

		static const UINT FrameCount = 2; 
		//Pipeline objects
		MSWRL::ComPtr<IDXGISwapChain3> m_swapChain;
		MSWRL::ComPtr<ID3D12Device> m_device; 
		MSWRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
		MSWRL::ComPtr<ID3D12PipelineState> m_pipelineState;
		MSWRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
		MSWRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
		MSWRL::ComPtr<ID3D12Resource> m_renderTargets[FrameCount]; 
		MSWRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator; 
		MSWRL::ComPtr<ID3D12RootSignature> m_rootSignature; 
		CD3DX12_VIEWPORT m_viewport;
		CD3DX12_RECT m_scissorRect;
		float m_aspectRatio;
		UINT m_rtvDescriptorSize;

		//App resources
		MSWRL::ComPtr<ID3D12Resource> m_vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView; 

		//Synchronization objects
		UINT m_frameIndex; 
		HANDLE m_fenceEvent; 
		MSWRL::ComPtr<ID3D12Fence> m_fence;
		UINT64 m_fenceValue; 
		void PopulateCommandList(); 
		void WaitForPreviousFrame();
		void LoadAssets(); 
	};
}