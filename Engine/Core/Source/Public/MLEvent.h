#pragma once
#pragma region Includes
#include "MLArray.h"
#include <functional>
#include "MLString.h"
#include "MLEventBase.h"
#pragma endregion 

namespace Core
{
	namespace Util
	{
		template <typename T> 
		class MLEvent : public MLEventBase
		{
		public: 
			MLEvent(const MLString& inKeyIdentifier);
			virtual ~MLEvent();
		private:
			MLArray<std::function<void(T)>> m_registeredDelegates;
		};
		template<typename T>
		inline MLEvent<T>::MLEvent(const MLString& inKeyIdentifier)
			:MLEventBase(inKeyIdentifier)
		{
		}
		template<typename T>
		inline MLEvent<T>::~MLEvent()
		{
		}
	}
}