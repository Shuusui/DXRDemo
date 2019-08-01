#pragma once
#pragma region Includes
#include "SharedEnums.h"
#pragma endregion

#define HELPER_FUNCTIONS_API __declspec(dllexport)

namespace Util
{
	namespace Rendering
	{
		struct HELPER_FUNCTIONS_API SResolution
		{
			const unsigned short WIDTH;
			const unsigned short HEIGHT;
		};
		static SResolution GetResolution(const EResolution& res)
		{
			switch (res)
			{
			case EResolution::FULL_HD:
				return SResolution{ 1920, 1080 };
			}
			return SResolution{};
		}
	}
	class HELPER_FUNCTIONS_API HelperFunctions
	{
		HelperFunctions(); 

		~HelperFunctions();
	};
}