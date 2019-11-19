#pragma once
#include "vulkan/vulkan.h"
#include <vector>
#define VULKAN_API __declspec(dllexport)

namespace Rendering
{
	namespace Vulkan
	{
		const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
		};

#ifdef NDEBUG
		const bool bEnableValidationLayers = false;
#else
		const bool bEnableValidationLayers = true;
#endif

		class VULKAN_API Vulkan
		{
		public:
			Vulkan();
			void Init();
			void Destroy();
		private:
			bool CheckValidationLayerSupport();
			void CreateInstance();
			void SetupDebugMessenger();
			std::vector<const char*> GetRequiredExtensions();

			static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
				const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
				const VkAllocationCallbacks* allocator,
				VkDebugUtilsMessengerEXT* debugMessenger);
			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
				void* userData);

			VkInstance m_instance;
			VkDebugUtilsMessengerEXT m_debugMessenger;
		};
	}
}