#pragma once

#pragma region Includes
#include <string>
#include "d3dx12.h"
#include <stdexcept>
#pragma endregion

namespace Rendering
{
	static inline std::string HrToString(const HRESULT& hr)
	{
		char str[64] = {};
		sprintf_s(str, "HRESULT of 0x%08X", static_cast<UINT>(hr)); 
		return std::string(str); 
	}
	class HrException : public std::runtime_error
	{
	public:
		HrException(const HRESULT& hr) 
			:std::runtime_error(HrToString(hr)), m_hr(hr) {}
		HRESULT Error() const { return m_hr; }
	private: 
		const HRESULT m_hr; 
	};

	static inline void ThrowIfFailed(const HRESULT& hr)
	{
		if (FAILED(hr))
		{
			throw HrException(hr);
		}
	}

	static inline void GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter)
	{
		*ppAdapter = nullptr; 
		for (UINT adapterIndex = 0;; ++adapterIndex)
		{
			IDXGIAdapter1* pAdapter = nullptr; 
			if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(adapterIndex, &pAdapter))
			{
				break;
			}
			if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
			{
				*ppAdapter = pAdapter;
				return;
			}
			pAdapter->Release();
		}
	}
}