#pragma once
#include <vector>
#include <optional>
#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX
#include "vulkan/vulkan.h"
#include <string>
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

		const std::vector<const char*> VALIDATION_LAYERS = 
		{
			"VK_LAYER_KHRONOS_validation"
		};
		const std::vector<const char*> DEVICE_EXTENSIONS = 
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		const int32_t MAX_FRAMES_IN_FLIGHT = 2;

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
			void CreateImageViews();
			void CreateRenderPass();
			void CreateGraphicsPipeline();
			void CreateFrameBuffers();
			void CreateCommandPool();
			void CreateCommandBuffers();
			void CreateSyncObjects();

			void DrawFrame();

			std::vector<const char*> GetRequiredExtensions();
			[[nodiscard]] QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice& device) const;
			[[nodiscard]] int32_t RateDeviceSuitability(const VkPhysicalDevice& device) const;
			[[nodiscard]] SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice& device) const;
			[[nodiscard]] VkShaderModule CreateShaderModule(const std::vector<char>& code) const;

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
			[[nodiscard]] bool IsDeviceSuitable(const VkPhysicalDevice& device) const;
			static bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);
			static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			static VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			static std::vector<char> ReadFile(const std::string& fileName);

			VkInstance m_instance;
			VkDebugUtilsMessengerEXT m_debugMessenger;
			VkDevice m_logicalDevice;
			VkPhysicalDevice m_physicalDevice;
			VkQueue m_graphicsQueue;
			VkSurfaceKHR m_surface;
			HWND m_windowHandle;
			HINSTANCE m_hInstance;
			VkQueue m_presentQueue;
			VkSwapchainKHR m_swapchain;
			std::vector<VkImage> m_swapChainImages;
			VkFormat m_swapChainImageFormat;
			VkExtent2D m_swapChainExtent;
			std::vector<VkImageView> m_swapChainImageViews;
			VkRenderPass m_renderPass;
			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_graphicsPipeline;
			std::vector<VkFramebuffer> m_swapChainFramebuffers;
			VkCommandPool m_commandPool;
			std::vector<VkCommandBuffer> m_commandBuffers;
			std::vector<VkSemaphore> m_imageAvailableSemaphores;
			std::vector<VkSemaphore> m_renderFinishedSemaphores;
			std::vector<VkFence> m_inFlightFences;
			std::vector<VkFence> m_imagesInFlight;
			size_t m_currentFrame;
		};
	}
}