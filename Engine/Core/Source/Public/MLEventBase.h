#pragma once
#pragma region Includes
#include <string>
#pragma endregion //Includes

namespace Core
{
	namespace Util
	{
		class MLEventBase
		{
		public: 
			MLEventBase(const std::string& inKeyIdentifier);
			virtual ~MLEventBase();
		private: 
			std::string m_keyIdentifier;
		};
		inline MLEventBase::MLEventBase(const std::string& inKeyIdentifier)
			:m_keyIdentifier(inKeyIdentifier)
		{

		}

		inline MLEventBase::~MLEventBase()
		{

		}
	}
}