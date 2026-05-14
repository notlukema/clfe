#include "Opengl4_6_i.h"

#include "./glad/glad.h"
#include "clfe/Log.h"

namespace clfe
{

	const char* const Pipeline_OpenGL4_6::Name = "OpenGL 4.6 Pipeline";

	GL4_6_Extension* Pipeline_OpenGL4_6::defaultExtension()
	{
#if defined(CLFE_OS_WIN)
		return new GL4_6_Extension_Windows();
#elif defined(CLFE_OS_MAC)
		return nullptr;
#elif defined(CLFE_OS_LINUX)
		return nullptr;
#else
		return nullptr;
#endif
	}

	//

	Pipeline_OpenGL4_6::Pipeline_OpenGL4_6(GL4_6_Extension* extension) : extension(extension)
	{
		if (extension == nullptr)
		{
			this->extension = defaultExtension();
		}
		if (this->extension == nullptr)
		{
			CLFE_ERROR("OpenGL 4.6 pipeline is not naturally supported!");
		}
	}

	Pipeline_OpenGL4_6::~Pipeline_OpenGL4_6()
	{
		delete extension;
	}

	PipelineData Pipeline_OpenGL4_6::getData()
	{
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		return PipelineData(
			Name,
			reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
			reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
			reinterpret_cast<const char*>(glGetString(GL_VERSION)),
			major,
			minor
		);
	}

	bool Pipeline_OpenGL4_6::compatible(Window* window)
	{
		return extension->compatible(window);
	}

	bool Pipeline_OpenGL4_6::attachWindow(Window* window)
	{
		return extension->initWindow(window);
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
		//extension->makeCurrent();
	}

}