#pragma once
#pragma region Includes
#include "ObjBase.h"
#include "stdint.h"
#pragma endregion //Includes


namespace Core
{
	namespace Util
	{
		/** 
		* Globally unique identifier
		*/
		struct MLGuid
		{
			/**
			* Default Constructor which will initialize all four parts of the MLGuid with 0
			*/
			MLGuid()
				:G(NULL)
				, U(NULL)
				, I(NULL)
				, D(NULL)
			{
			}
			/**
			* Constructor which will initialize the MLGuid with microsoft implementation of MLGuid
			*
			* @param inGuid microsoft Guid implementation which will initialize the four parts of the MLGuid with the four parts of microsofts MLGuid
			*/
			MLGuid(const GUID& inGuid)
				:G(inGuid.Data1)
				, U(static_cast<uint32_t>(inGuid.Data2))
				, I(inGuid.Data3)
				, D(inGuid.Data4[3]<<24 | inGuid.Data4[2]<<16 | inGuid.Data4[1]<<8 | inGuid.Data4[0])
			{
			}

			/**
			* statically create a new MLGuid
			*
			* @return the new generated MLGuid
			*/
			static MLGuid NewMLGuid();
			/**
			* Getter function which will return first part of the MLGuid
			*
			* @return the first (G) part of the MLGuid
			*/
			uint32_t GetG() const
			{
				return G;
			}
			/**
			* Getter function which will return second part of the MLGuid
			*
			*@return the second (U) part of the MLGuid
			*/
			uint32_t GetU() const
			{
				return U;
			}
			/**
			* Getter function which will return third part of the MLGuid
			*
			*@return the third (I) part of the MLGuid
			*/
			uint32_t GetI() const
			{
				return I;
			}
			/**
			* Getter function which will return fourth part of the MLGuid
			*
			*@return the fourth (D) part of the MLGuid
			*/
			uint32_t GetD() const
			{
				return D;
			}
			/**
			* operator overload for the equal-equal operator
			* 
			* @param other Other MLGuid to compare with 
			* @return result of the comparison
			*/
			bool operator==(const MLGuid& other) const;
			/**
			* operator overload for the equal-equal operator (this overload is mostly used to check if the MLGuid is null)
			* 
			* @param inNum number to compare with the MLGuid
			* @return true or false if the comparison is right
			*/
			bool operator==(const uint32_t& inNum) const;
			/**
			* function to check if the MLGuid is null 
			* 
			* @return true if the MLGuid is null or false if it is already initialized
			*/
			bool IsNull() const;
		private:
			uint32_t G;
			uint32_t U;
			uint32_t I;
			uint32_t D;
		};
	}
}
__forceinline Core::Util::MLGuid Core::Util::MLGuid::NewMLGuid()
{
	GUID outGuid = {};
	if (CoCreateGuid(&outGuid) != S_OK)
	{
		//TODO: implement error messaging here
		return {};
	}
	return { outGuid };
}

inline bool Core::Util::MLGuid::operator==(const MLGuid& other) const
{
	return this->G == other.G && this->U == other.U && this->I == other.I && this->D == other.D;
}

inline bool Core::Util::MLGuid::operator==(const uint32_t& inNum) const
{
	return (this->G + this->U + this->I + this->D) == inNum;
}

inline bool Core::Util::MLGuid::IsNull() const
{
	return *this == NULL;
}
