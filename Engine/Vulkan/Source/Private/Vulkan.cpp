#include "../Public/Vulkan.h"
#include <stdexcept>
#include <iostream>

Rendering::Vulkan::Vulkan::Vulkan()
	:m_instance(nullptr)
{
}

void Rendering::Vulkan::Vulkan::Init()
{
	CreateInstance();
	SetupDebugMessenger();
}

void Rendering::Vulkan::Vulkan::Destroy()
{
	if(bEnableValidationLayers)
	{
		DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
	}

	vkDestroyInstance(m_instance, nullptr);
}

bool Rendering::Vulkan::Vulkan::CheckValidationLayerSupport()
{
	uint32_t layerCount = 0;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for(const char* layer : validationLayers)
	{
		bool bLayerFound = false;
		for(const VkLayerProperties& layerProperties : availableLayers)
		{
			if(strcmp(layer, layerProperties.layerName) == 0)
			{
				bLayerFound = true;
				break;
			}
		}
		if(!bLayerFound)
		{
			return false;
		}
	}
	return true;
}

void Rendering::Vulkan::Vulkan::CreateInstance()
{
	if(bEnableValidationLayers && !CheckValidationLayerSupport())
	{
		throw std::runtime_error("validation layers requested, but not available");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Murphys Law";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = 0;

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	if(bEnableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		PopulateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}
	const std::vector<const char*>& extensions = GetRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
	if(result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance!");
	}
}

void Rendering::Vulkan::Vulkan::SetupDebugMessenger()
{
	if constexpr (!bEnableValidationLayers)
	{
		return;
	}
	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	PopulateDebugMessengerCreateInfo(createInfo);

	if(CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to set up debug messenger");
	}
}

VkResult Rendering::Vulkan::Vulkan::CreateDebugUtilsMessengerEXT(VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* createInfo, const VkAllocationCallbacks* allocator,
	VkDebugUtilsMessengerEXT* debugMessenger)
{
	const auto function = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if(function)
	{
		return function(instance, createInfo, allocator, debugMessenger);
	}
	return VK_ERROR_EXTENSION_NOT_PRESENT;
}

std::vector<const char*> Rendering::Vulkan::Vulkan::GetRequiredExtensions()
{
	std::vector<const char*> extensions = {};
	if(bEnableValidationLayers)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	return extensions;
}

void Rendering::Vulkan::Vulkan::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallback;
	createInfo.pUserData = nullptr;
}

VkBool32 Rendering::Vulkan::Vulkan::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
	void* userData)
{
	std::cerr << "Validation layer: " << callbackData->pMessage << std::endl;
	if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		
	}
	return VK_FALSE;
}

void Rendering::Vulkan::Vulkan::DestroyDebugUtilsMessengerEXT(VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* allocator)
{
	const auto function = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if(function != nullptr)
	{
		function(instance, debugMessenger, allocator);
	}
}
