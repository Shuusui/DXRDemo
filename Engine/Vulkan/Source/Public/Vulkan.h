#pragma once
#include <vector>
#include <optional>
#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX
#include "vulkan/vulkan.h"
#define VULKAN_API __declspec(dllexport)

namespace Rendering
{
	namespace Vulkan
	{
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> GraphicsFamily;
			std::optional<uint32_t> PresentFamily;

			[[nodiscard]]bool IsComplete() const
			{
				return GraphicsFamily.has_value() && PresentFamily.has_value();
			}
		};


		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR Capabilities;
			std::vector<VkSurfaceFormatKHR> Formats;
			std::vector<VkPresentModeKHR> PresentModes;

			[[nodiscard]] bool IsEmpty() const
			{
				return Formats.empty() && PresentModes.empty();
			}
		};

		const std::vector<const char*> VALIDATION_LAYERS = {
		"VK_LAYER_KHRONOS_validation"
		};
		const std::vector<const char*> DEVICE_EXTENSIONS = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};

#ifdef _DEBUG
		const bool bEnableValidationLayers = true;
#else
		const bool bEnableValidationLayers = false;
#endif

		class VULKAN_API Vulkan
		{
		public:
			Vulkan(const HWND& windowHandle, const HINSTANCE& hInstance);
			void Init();
			void Run();
			void Destroy();
		private:
			static bool CheckValidationLayerSupport();
			void CreateInstance();
			void SetupDebugMessenger();
			void CreateSurface();
			void PickPhysicalDevice();
			void CreateLogicalDevice();
			void CreateSwapChain();

			std::vector<const char*> GetRequiredExtensions();
			[[nodiscard]] QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device) const;
			[[nodiscard]] int32_t RateDeviceSuitability(const VkPhysicalDevice& device) const;
			[[nodiscard]] SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device) const;

			static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

			static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
				const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
				const VkAllocationCallbacks* allocator,
				VkDebugUtilsMessengerEXT* debugMessenger);
			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
				void* userData);
			static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
				VkDebugUtilsMessengerEXT debugMessenger,
				const VkAllocationCallbacks* allocator);
			static bool IsDeviceSuitable(const VkPhysicalDevice& device);
			static bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);
			static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

			VkInstance m_instance;
			VkDebugUtilsMessengerEXT m_debugMessenger;
			VkDevice m_logicalDevice;
			VkPhysicalDevice m_physicalDevice;
			VkQueue m_graphicsQueue;
			VkSurfaceKHR m_surface;
			HWND m_windowHandle;
			HINSTANCE m_hInstance;
			VkQueue m_presentQueue;
		};
	}
}