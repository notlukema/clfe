#ifndef CLFE_PIPELINE_OPENGL4_6_H
#define CLFE_PIPELINE_OPENGL4_6_H

#include "../impl/Pipeline.h"
#include "clfe/window/Window.h"

#if defined(CLFE_OS_WIN)
#include "Windows_i.h"

#elif defined(CLFE_OS_MAC)
//#include "MacWnd_i.h"

#elif defined(CLFE_OS_LINUX)
//#include "LinuxWnd_i.h"

#else
#error "Unsupported platform for OpenGL 4.6 pipeline!"

#endif

namespace clfe
{

	class Pipeline_OpenGL4_6 : public Pipeline
	{
	public: // Standard pipeline components
		static const char* const Name;

	private:
		friend class OpenGL4_6_Initializer;

	public:
		Pipeline_OpenGL4_6();
		~Pipeline_OpenGL4_6() override;

		virtual bool attachWindow(Window* window) override;
		virtual bool detachWindow(Window* window) override;

		virtual bool attachScene(Scene* scene) override;
		virtual bool detachScene(Scene* scene) override;

		virtual void draw() override;

	};

}

#endif