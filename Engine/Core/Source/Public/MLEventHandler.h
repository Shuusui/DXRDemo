#pragma once
#pragma region Includes
#include "MLString.h"
#include "MLEventBase.h"
#include "MLMap.h"
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
			void RegisterMLEvent(MLEventBase* inMLEvent);
			~MLEventHandler();
		private:
			MLEventHandler();
			static MLEventHandler* s_MLEventHandlerHandle;
			//MLMap<MLString, MLEventBase*> m_registeredMLEvents; 
		};
	}
}