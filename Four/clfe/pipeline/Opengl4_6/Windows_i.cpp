#include "Windows_i.h"

namespace clfe
{

	const char* const Pipeline_OpenGL4_6_Windows::Name = "OpenGL 4.6 Windows Pipeline";
	const PipelineEntry Pipeline_OpenGL4_6_Windows::Entry = PipelineEntry(new Pipeline_OpenGL4_6_Windows());

	//

	Pipeline_OpenGL4_6_Windows::Pipeline_OpenGL4_6_Windows()
	{
		// Empty
	}

	Pipeline_OpenGL4_6_Windows::~Pipeline_OpenGL4_6_Windows()
	{
		// Empty
	}

	bool Pipeline_OpenGL4_6_Windows::init()
	{
		return false;
	}

	void Pipeline_OpenGL4_6_Windows::initWindow(Window* window)
	{
		// Empty
	}

}