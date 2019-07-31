#pragma once
#pragma region Includes
#include "MLPair.h"
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		class MLTree
		{
		public: 
			MLTree();
			~MLTree();
		private: 
			MLPairBase* m_keyValueMLPairs;
		};

		inline MLTree::MLTree()
			:m_keyValueMLPairs(nullptr)
		{
		}

		inline MLTree::~MLTree()
		{
		}

	}
}