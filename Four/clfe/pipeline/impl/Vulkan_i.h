#ifndef CLFE_PIPELINE_GLOBAL_VULKAN_H
#define CLFE_PIPELINE_GLOBAL_VULKAN_H

#include <vulkan/vulkan.h>

#include <cstdint>

namespace clfe
{

	class GlobalVulkan
	{
	private:
		VkInstance instance;

	public:
		static bool init(VkInstanceCreateInfo createInfo, uint32_t apiVersion);

	};

}

#endif