#ifndef CLFE_PIPELINE_OPENGL4_6_H
#define CLFE_PIPELINE_OPENGL4_6_H

#include "../impl/Pipeline.h"
#include "clfe/window/Window.h"

namespace clfe
{

	class Pipeline_OpenGL4_6;

	class GL4_6_Extension
	{
	protected:
		friend class Pipeline_OpenGL4_6;

		GL4_6_Extension() = default;

	public:
		virtual ~GL4_6_Extension() = default;

		virtual bool compatible(Window* window) = 0;
		virtual bool initWindow(Window* window) = 0;

	};

	class Pipeline_OpenGL4_6 : public Pipeline
	{
	public:
		static const char* const Name;

		static GL4_6_Extension* defaultExtension();

	private:
		friend class GL4_6_Extension;
		GL4_6_Extension* extension;

	public:
		Pipeline_OpenGL4_6(GL4_6_Extension* extension = nullptr);
		~Pipeline_OpenGL4_6() override;

		virtual bool compatible(Window* window) override;
		virtual bool attachWindow(Window* window) override;
		virtual bool detachWindow(Window* window) override;

		virtual bool attachScene(Scene* scene) override;
		virtual bool detachScene(Scene* scene) override;

		virtual void draw() override;

	};

}

#if defined(CLFE_OS_WIN)
#include "Windows_i.h"

#elif defined(CLFE_OS_MAC)
//#include "MacWnd_i.h"

#elif defined(CLFE_OS_LINUX)
//#include "LinuxWnd_i.h"

#else
#warning "Unsupported platform for OpenGL 4.6 pipeline!"

#endif

#endif