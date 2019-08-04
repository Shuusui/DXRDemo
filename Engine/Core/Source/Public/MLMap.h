#pragma once
#pragma region Includes
#include "MLPair.h"
#include <map>
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
			MLMap(const std::initializer_list<MLPair<T1, T2>>& inInitializerList);
			~MLMap();
		private: 
			std::map<T1, T2> m_map;
		};
		template<typename T1, typename T2>
		MLMap<T1, T2>::MLMap()
			:m_map({})
		{
		}

		template <typename T1, typename T2>
		MLMap<T1, T2>::MLMap(const std::initializer_list<MLPair<T1, T2>>& inInitializerList)
			:m_map(inInitializerList)
		{
		}

		template<typename T1, typename T2>
		MLMap<T1, T2>::~MLMap()
		{
		}
	}
}