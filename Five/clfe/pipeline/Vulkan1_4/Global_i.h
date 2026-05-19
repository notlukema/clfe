#ifndef CLFE_PIPELINE_VULKAN1_4_GLOBAL_I_H
#define CLFE_PIPELINE_VULKAN1_4_GLOBAL_I_H

#include <vulkan/vulkan.h>
#include <cstdint>

namespace clfe
{

	class Pipeline_Vulkan1_4_Global
	{
	private:
		VkInstance instance;

	public:
		static bool init();

	};

}

#endif