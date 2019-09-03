#pragma once
#pragma region Includes
#include "MLString.h"
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		class MLEventBase
		{
		public: 
			MLEventBase(const MLString& inKeyIdentifier)
				:m_keyIdentifier(inKeyIdentifier)
			{
			}
			virtual ~MLEventBase();
		private: 
			MLString m_keyIdentifier;
		};
	}
}