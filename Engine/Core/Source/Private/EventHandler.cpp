#include "../Public/MLEventHandler.h"

Core::Util::MLEventHandler* Core::Util::MLEventHandler::s_MLEventHandlerHandle = nullptr;

void Core::Util::MLEventHandler::Create()
{
	if (!s_MLEventHandlerHandle)
	{
		s_MLEventHandlerHandle = new MLEventHandler();
	}
}

Core::Util::MLEventHandler* Core::Util::MLEventHandler::GetHandle()
{
	return s_MLEventHandlerHandle;
}

void Core::Util::MLEventHandler::RegisterMLEvent(MLEventBase* inMLEvent)
{
}

Core::Util::MLEventHandler::~MLEventHandler()
{
	delete s_MLEventHandlerHandle;
	s_MLEventHandlerHandle = nullptr;
}
