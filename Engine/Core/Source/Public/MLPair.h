#pragma once
#pragma region Includes
#include <tuple>
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		template <typename T1, typename T2>
		class MLPair
		{
		public:
			MLPair();
			explicit MLPair(const T1& key, const T2& value = {});
			MLPair(const MLPair& other);
			~MLPair();
		private:
			std::tuple<T1, T2> m_pair;
		};
		template<typename T1, typename T2>
		MLPair<T1, T2>::MLPair()
			:m_pair({})
		{

		}

		template <typename T1, typename T2>
		MLPair<T1, T2>::MLPair(const T1& key, const T2& value)
			:m_pair(std::tuple<T1, T2>(key, value))
		{
		}

		template <typename T1, typename T2>
		MLPair<T1, T2>::MLPair(const MLPair& other)
			:m_pair(other.m_pair)
		{
		}

		template<typename T1, typename T2>
		MLPair<T1, T2>::~MLPair()
		{
		}
	}
}