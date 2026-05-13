#include "Opengl4_6_i.h"

#include "./glad/glad.h"

namespace clfe
{

	const char* const Pipeline_OpenGL4_6::Name = "OpenGL 4.6 Pipeline";

	//

	Pipeline_OpenGL4_6::Pipeline_OpenGL4_6()
	{
	}

	Pipeline_OpenGL4_6::~Pipeline_OpenGL4_6()
	{
		// Empty
	}

	bool Pipeline_OpenGL4_6::attachWindow(Window* window)
	{
		return false;
	}

	bool Pipeline_OpenGL4_6::detachWindow(Window* window)
	{
		return false;
	}

	bool Pipeline_OpenGL4_6::attachScene(Scene* scene)
	{
		return false;
	}

	bool Pipeline_OpenGL4_6::detachScene(Scene* scene)
	{
		return false;
	}

	void Pipeline_OpenGL4_6::draw()
	{

	}

}