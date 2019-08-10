#pragma once
#pragma region Includes
#include "ObjBase.h"
#include <cstdint>
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
				, D(nullptr)
			{
			}
			/**
			* Constructor which will initialize the MLGuid with microsoft implementation of MLGuid
			*
			* @param inGuid microsoft Guid implementation which will initialize the four parts of the MLGuid with the four parts of microsofts MLGuid
			*/
			explicit MLGuid(GUID& inGuid)
				:G(inGuid.Data1)
				, U(inGuid.Data2)
				, I(inGuid.Data3)
				, D(inGuid.Data4)
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
			uint64_t GetG() const
			{
				return G;
			}
			/**
			* Getter function which will return second part of the MLGuid
			*
			*@return the second (U) part of the MLGuid
			*/
			uint16_t GetU() const
			{
				return U;
			}
			/**
			* Getter function which will return third part of the MLGuid
			*
			*@return the third (I) part of the MLGuid
			*/
			uint16_t GetI() const
			{
				return I;
			}
			/**
			* Getter function which will return fourth part of the MLGuid
			*
			*@return the fourth (D) part of the MLGuid
			*/
			uint8_t* GetD() const
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
			 * operator overload for the not-equal operator
			 * 
			 * @param other Other MLGuid to compare with
			 * @return result of the dissimilarity
			 */
			bool operator!=(const MLGuid& other) const;
			/**
			* function to check if the MLGuid is null
			*
			*
			* @return true if the MLGuid is null or false if it is already initialized
			*/
			bool IsNull() const;
		private:
			uint64_t G;
			uint16_t U;
			uint16_t I;
			uint8_t* D;
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
	return MLGuid(outGuid);
}

inline bool Core::Util::MLGuid::operator==(const MLGuid& other) const
{
	return this->G == other.G && this->U == other.U && this->I == other.I && this->D == other.D;
}

inline bool Core::Util::MLGuid::operator!=(const MLGuid& other) const
{
	return this->G != other.G || this->U != other.U || this->I != other.I || this->D != other.D;
}

inline bool Core::Util::MLGuid::IsNull() const
{
	return *this == MLGuid();
}
