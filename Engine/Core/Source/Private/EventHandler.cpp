#include "../Public/MLEventHandler.h"

Core::Util::MLEventHandler* Core::Util::MLEventHandler::s_eventHandlerHandle = nullptr;

void Core::Util::MLEventHandler::Create()
{
	if (!s_eventHandlerHandle)
	{
		s_eventHandlerHandle = new MLEventHandler();
	}
}

Core::Util::MLEventHandler* Core::Util::MLEventHandler::GetHandle()
{
	return s_eventHandlerHandle;
}

void Core::Util::MLEventHandler::RegisterEvent(MLEventBase* inMLEvent)
{
}

Core::Util::MLEventHandler::~MLEventHandler()
{
	delete s_eventHandlerHandle;
	s_eventHandlerHandle = nullptr;
}
