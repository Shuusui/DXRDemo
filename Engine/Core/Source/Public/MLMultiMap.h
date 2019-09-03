#pragma once
#pragma region Includes
#include <map>
#include "MLPair.h"
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		template<typename T1, typename T2> 
		class MLMultiMap
		{
		public:
			MLMultiMap()
				:m_multiMap({})
			{
				
			}
			MLMultiMap(const std::initializer_list<MLPair<T1, T2>>& inPair)
				:m_multiMap(inPair)
			{
			}
			MLMultiMap(const MLMultiMap& other)
				:m_multiMap(other.m_multiMap)
			{
			}
			~MLMultiMap() = default;

			void Add(const MLPair<T1, T2>& inPair)
			{
				m_multiMap.insert(inPair);
			}
		private:
			std::multimap<T1, T2> m_multiMap;
		};

	}
}