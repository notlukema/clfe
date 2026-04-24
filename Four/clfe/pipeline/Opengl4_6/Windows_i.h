#ifndef CLFE_PIPELINE_OPENGL4_6_WINDOWS_H
#define CLFE_PIPELINE_OPENGL4_6_WINDOWS_H

#include "../impl/Pipeline.h"
#include "../impl/PixelFormat.h"
#include "clfe/window/Window.h"

#include <Windows.h>

namespace clfe
{
	
	class Pipeline_OpenGL4_6_Windows : public Pipeline
	{
	public: // Standard pipeline components
		static const char* const Name;

	public:
		Pipeline_OpenGL4_6_Windows(PixelFormat format = PixelFormat(), Window* window = nullptr);
		Pipeline_OpenGL4_6_Windows(PIXELFORMATDESCRIPTOR pfd, Window* window = nullptr);
		~Pipeline_OpenGL4_6_Windows() override;

	};

}

#endif