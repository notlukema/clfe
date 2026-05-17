#include "Vulkan_i.h"

namespace clfe
{

	bool GlobalVulkan::init(VkInstanceCreateInfo createInfo, uint32_t apiVersion)
	{
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.pApplicationInfo = nullptr;
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = nullptr;
		createInfo.enabledExtensionCount = 0;
		createInfo.ppEnabledExtensionNames = nullptr;

		VkInstance instance;
		return vkCreateInstance(&createInfo, nullptr, &instance) == VK_SUCCESS;
	}

}