#pragma once

#pragma region Includes
#include <string>
#include "d3dx12.h"
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
}