#pragma once
#pragma region Includes
#include <functional>
#include <string>
#include "MLEventBase.h"
#include <vector>
#pragma endregion 

namespace Core
{
	namespace Util
	{
		template <typename T> 
		class MLEvent : public MLEventBase
		{
		public: 
			MLEvent(const std::string& inKeyIdentifier);
			virtual ~MLEvent();
		private:
			std::vector<std::function<void(T)>> m_registeredDelegates;
		};
		template<typename T>
		MLEvent<T>::MLEvent(const std::string& inKeyIdentifier)
			:MLEventBase(inKeyIdentifier)
		{
		}
		template<typename T>
		MLEvent<T>::~MLEvent()
		{
		}
	}
}