#ifndef CLFE_PIPELINE_VULKAN1_4_H
#define CLFE_PIPELINE_VULKAN1_4_H

#include "../impl/Pipeline.h"
#include "../impl/Vulkan_i.h"
#include "clfe/window/Window.h"

namespace clfe
{

	class Pipeline_Vulkan1_4;

	class Vulkan1_4_Extension
	{
	protected:
		friend class Pipeline_Vulkan1_4;

		Vulkan1_4_Extension() = default;

	public:
		virtual ~Vulkan1_4_Extension() = default;

		virtual bool compatible(Window* window) = 0;
		virtual bool initWindow(Window* window) = 0;

		virtual bool makeCurrent(Window* window = nullptr) = 0;

	};

	class Pipeline_Vulkan1_4 : public Pipeline
	{
	public:
		static const char* const Name;

		static Vulkan1_4_Extension* defaultExtension();

	private:
		friend class Vulkan1_4_Extension;
		Vulkan1_4_Extension* extension;

	public:
		Pipeline_Vulkan1_4(Vulkan1_4_Extension* extension = nullptr);
		~Pipeline_Vulkan1_4() override;

		virtual PipelineData getData() override;

		virtual bool compatible(Window* window) override;
		virtual bool attachWindow(Window* window) override;
		virtual bool detachWindow(Window* window) override;

		virtual bool attachScene(Scene* scene) override;
		virtual bool detachScene(Scene* scene) override;

		virtual void draw() override;

	};

}

#if defined(CLFE_OS_WIN)
//#include "Windows_i.h"

#elif defined(CLFE_OS_MAC)
//#include "MacWnd_i.h"

#elif defined(CLFE_OS_LINUX)
//#include "LinuxWnd_i.h"

#else
#warning "Unsupported platform for Vulkan 1.4 pipeline!"

#endif

#endif