#pragma once
#pragma region Includes
#include "MLArray.h"
#include <functional>
#include "MLString.h"
#pragma endregion 

namespace Core
{
	namespace Util
	{
		template <typename T1, typename T2> 
		class MLEvent
		{
		public:
			MLEvent(std::function<T1(T2)>)
			{
			}

			~MLEvent()
			{
				
			}
		private:
			MLArray<std::function<T1(T2)>> m_registeredDelegates;
		};
	}
}