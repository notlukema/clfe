#include "Windows_i.h"

#include "../impl/WindowsUtils.h"
#include "./glad/glad.h"

namespace clfe
{

	const char* const Pipeline_OpenGL4_6_Windows::Name = "OpenGL 4.6 Windows Pipeline";

	//

	void innerInit(PIXELFORMATDESCRIPTOR pfd, Window* window)
	{
		if (window == nullptr)
		{
		}
	}

	Pipeline_OpenGL4_6_Windows::Pipeline_OpenGL4_6_Windows(PixelFormat format, Window* window) : Pipeline(System::genNextID())
	{
		innerInit(WindowsUtils::convertToWindowsFormat(format), window);
	}

	Pipeline_OpenGL4_6_Windows::Pipeline_OpenGL4_6_Windows(PIXELFORMATDESCRIPTOR pfd, Window* window) : Pipeline(System::genNextID())
	{
		innerInit(pfd, window);
	}

	Pipeline_OpenGL4_6_Windows::~Pipeline_OpenGL4_6_Windows()
	{
		// Empty
	}

	void Pipeline_OpenGL4_6_Windows::initWindow(Window* window)
	{
		// Empty
	}

}