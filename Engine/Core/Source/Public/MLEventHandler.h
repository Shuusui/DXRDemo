#pragma once
#pragma region Includes
#include "MLString.h"
#include "MLEventBase.h"
#include "MLMultiMap.h"
#pragma endregion //Includes



namespace Core
{
	namespace Util
	{
		class MLEventHandler
		{
		public:
			static void Create();
			static MLEventHandler* GetHandle();
			void RegisterEvent(const MLString& inEventIdentifier, const MLEventBase& inMLEvent);
			~MLEventHandler();
		private:
			MLEventHandler() = default;
			static MLEventHandler* s_eventHandlerHandle;
			MLMultiMap<MLString, MLEventBase> m_registeredMLEvents;
		};
	}
}