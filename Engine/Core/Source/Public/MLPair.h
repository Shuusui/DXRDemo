#pragma once
#pragma region Includes
#include "MLPairBase.h"
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		template <typename T1, typename T2>
		class MLPair : public MLPairBase
		{
		public:
			MLPair();
			~MLPair();
		private:
			T1 m_key; 
			T2 m_value;
		};
		template<typename T1, typename T2>
		MLPair<T1, T2>::MLPair()
		{
		}

		template<typename T1, typename T2>
		MLPair<T1, T2>::~MLPair()
		{
		}
	}
}