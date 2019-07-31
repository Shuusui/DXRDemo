#pragma once
#pragma region Includes
#include "MLTree.h"
#include "MLPair.h"
#pragma endregion //Includes


namespace Core
{
	namespace Util
	{
		template <typename T1, typename T2>
		class MLMap
		{
		public: 
			MLMap();
			~MLMap();
		private: 
			MLTree m_MLTree;
		};
		template<typename T1, typename T2>
		inline MLMap<T1, T2>::MLMap()
		{

		}
		template<typename T1, typename T2>
		inline MLMap<T1, T2>::~MLMap()
		{
		}
	}
}