#pragma once

#pragma region Includes
#include "d3dx12.h"
#include "dxgi.h"

#pragma endregion



namespace Rendering
{
	namespace MSWRL = Microsoft::WRL; 
	class DX12
	{
	public: 

		DX12();
		~DX12();
		void Init();

	private: 
		//Pipeline objects
		
		MSWRL::ComPtr<IDXGISwapChain> m_swapChain;
		MSWRL::ComPtr<ID3D12Device> m_device; 
		MSWRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
		MSWRL::ComPtr<ID3D12PipelineState> m_pipelineState;
		MSWRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
		
		//App resources
		MSWRL::ComPtr<ID3D12Resource> m_vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView; 

		//Synchronization objects
		UINT m_frameIndex; 
		HANDLE m_fenceEvent; 
		MSWRL::ComPtr<ID3D12Fence> m_fence;
		UINT64 m_fenceValue; 

	};
}