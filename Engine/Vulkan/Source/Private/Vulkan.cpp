#include "../Public/Vulkan.h"
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

Rendering::Vulkan::Vulkan::Vulkan(const HWND& windowHandle, const HINSTANCE& hInstance)
	:m_instance(nullptr)
	,m_physicalDevice(VK_NULL_HANDLE)
	,m_windowHandle(windowHandle)
	,m_hInstance(hInstance)
{
}

void Rendering::Vulkan::Vulkan::Init()
{
	CreateInstance();
	SetupDebugMessenger();
	CreateSurface();
	PickPhysicalDevice();
	CreateLogicalDevice();
	CreateSwapChain();

}

void Rendering::Vulkan::Vulkan::Run()
{
}

void Rendering::Vulkan::Vulkan::Destroy()
{
	if(bEnableValidationLayers)
	{
		DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
	}

	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyInstance(m_instance, nullptr);
	vkDestroyDevice(m_logicalDevice, nullptr);
}

bool Rendering::Vulkan::Vulkan::CheckValidationLayerSupport()
{
	uint32_t layerCount = 0;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for(const char* layer : VALIDATION_LAYERS)
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
		createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();

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

void Rendering::Vulkan::Vulkan::CreateSurface()
{
	VkWin32SurfaceCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hwnd = m_windowHandle;
	createInfo.hinstance = m_hInstance;
	createInfo.pNext = nullptr;
	createInfo.flags = NULL;

	VkResult Result = vkCreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &m_surface);
	if(Result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create window surface!");
	}
}

void Rendering::Vulkan::Vulkan::PickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
	if(deviceCount <= 0)
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support");
	}
	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, physicalDevices.data());

	//easy suitability check
	/*for(const VkPhysicalDevice& physicalDevice : physicalDevices)
	{
		if(IsDeviceSuitable(physicalDevice))
		{
			m_physicalDevice = physicalDevice;
			break;
		}
	}*/

	//rating system to find best physical device
	std::multimap<int, VkPhysicalDevice> candidates = {};
	for(const VkPhysicalDevice& physicalDevice : physicalDevices)
	{
		int32_t score = RateDeviceSuitability(physicalDevice);
		candidates.insert(std::make_pair(score, physicalDevice));
	}

	if(candidates.rbegin()->first >0)
	{
		m_physicalDevice = candidates.rbegin()->second;
	}
	else
	{
		throw std::runtime_error("failed to find suitable GPU");
	}


}

void Rendering::Vulkan::Vulkan::CreateLogicalDevice()
{
	QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);

	std::set<uint32_t> uniqueQueueFamilies = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(uniqueQueueFamilies.size());

	float queuePriority = 1.0f;
	uint32_t index = 0;
	for(const uint32_t& queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos[index] = queueCreateInfo;
		++index;
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(DEVICE_EXTENSIONS.size());
	createInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS.data();
	createInfo.enabledLayerCount = 0;
	if(bEnableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
		createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
	}

	if(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(m_logicalDevice, indices.GraphicsFamily.value(), 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_logicalDevice, indices.PresentFamily.value(), 0, &m_presentQueue);
}

void Rendering::Vulkan::Vulkan::CreateSwapChain()
{

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
		extensions.push_back("VK_KHR_win32_surface");
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
	//if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	//{
	//	
	//}
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

bool Rendering::Vulkan::Vulkan::IsDeviceSuitable(const VkPhysicalDevice& device)
{
	VkPhysicalDeviceProperties deviceProperties = {};
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures = {};
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
}

bool Rendering::Vulkan::Vulkan::CheckDeviceExtensionSupport(const VkPhysicalDevice& device)
{
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(DEVICE_EXTENSIONS.begin(), DEVICE_EXTENSIONS.end());

	for(const VkExtensionProperties& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}
	return requiredExtensions.empty();
}

VkSurfaceFormatKHR Rendering::Vulkan::Vulkan::ChooseSwapSurfaceFormat(
	const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for(const VkSurfaceFormatKHR& availableFormat : availableFormats)
	{
		if(availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR Rendering::Vulkan::Vulkan::ChooseSwapPresentMode(
	const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for(const VkPresentModeKHR& availablePresentMode : availablePresentModes)
	{
		if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Rendering::Vulkan::Vulkan::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if(capabilities.currentExtent.width != UINT32_MAX)
	{
		return capabilities.currentExtent;
	}
	else
	{
		VkExtent2D actualExtent = { 1920, 1090 };
		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
	}
	
}

int32_t Rendering::Vulkan::Vulkan::RateDeviceSuitability(const VkPhysicalDevice& device) const
{
	VkPhysicalDeviceProperties deviceProperties = {};
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures = {};
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int32_t score = 0;

	if(!deviceFeatures.geometryShader)
	{
		return score;
	}

	if(!CheckDeviceExtensionSupport(device))
	{
		return score;
	}

	if(QuerySwapChainSupport(device).IsEmpty())
	{
		return score;
	}

	score++;

	if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	{
		score += 1000;
	}
	score += deviceProperties.limits.maxImageDimension2D;

	QueueFamilyIndices indices = FindQueueFamilies(device);
	if(indices.IsComplete())
	{
		score += indices.GraphicsFamily.value();
	}

	return score;
}

Rendering::Vulkan::SwapChainSupportDetails Rendering::Vulkan::Vulkan::QuerySwapChainSupport(
	const VkPhysicalDevice& device) const
{
	SwapChainSupportDetails details = {};

	VkPhysicalDeviceProperties deviceProperties = {};
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures = {};
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	VkResult Result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.Capabilities);

	uint32_t formatCount = 0;
	Result = vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

	if(formatCount != 0)
	{
		details.Formats.resize(formatCount);
		Result = vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.Formats.data());
}

	uint32_t presentModeCount = 0;
	Result = vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

	if(presentModeCount != 0)
	{
		details.PresentModes.resize(presentModeCount);
		Result = vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.PresentModes.data());
	}

	return details;
}

Rendering::Vulkan::QueueFamilyIndices Rendering::Vulkan::Vulkan::FindQueueFamilies(const VkPhysicalDevice& device) const
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());


	for(int32_t i = 0; i <  queueFamilies.size(); ++i)
	{
		VkBool32 presentSupport = false;
		if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.GraphicsFamily = i;
		}
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
		if(presentSupport)
		{
			indices.PresentFamily = i;
		}
		if(indices.IsComplete())
		{
			break;
		}
	}

	return indices;
}
