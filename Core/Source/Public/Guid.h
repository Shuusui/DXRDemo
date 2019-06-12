#pragma once
#pragma region Includes
#include "ObjBase.h"
#include "stdint.h"
#pragma endregion //Includes


namespace Core
{
	namespace Util
	{
		struct Guid
		{
		public:
			Guid()
				:G(0)
				, U(0)
				, I(0)
				, D(0)
			{
			}
			Guid(const GUID& inGUID)
				:G(inGUID.Data1)
				, U(static_cast<uint32_t>(inGUID.Data2))
				, I(inGUID.Data3)
				, D(inGUID.Data4[3]<<24 | inGUID.Data4[2]<<16 | inGUID.Data4[1]<<8 | inGUID.Data4[0])
			{
			}
			static Guid NewGuid();
			uint32_t GetG() const
			{
				return G;
			}
			uint32_t GetU() const
			{
				return U;
			}
			uint32_t GetI() const
			{
				return I;
			}
			uint32_t GetD() const
			{
				return D;
			}
		private:
			uint32_t G;
			uint32_t U;
			uint32_t I;
			uint32_t D;
		};
	}
}
__forceinline Core::Util::Guid Core::Util::Guid::NewGuid()
{
	GUID outGUID = {};
	Guid outGuid = {};
	if (CoCreateGuid(&outGUID) != S_OK)
	{
		//TODO: implement error messaging here
		return outGuid;
	}
	Guid(GUID);
	return outGuid;
}
