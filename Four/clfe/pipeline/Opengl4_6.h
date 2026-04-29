#ifndef CLFE_PIPELINE_OPENGL4_6_H
#define CLFE_PIPELINE_OPENGL4_6_H

#include "clfe/CrossPlatform.h"

#if defined(CLFE_OS_WIN)
#include "Opengl4_6/Windows_i.h"
namespace clfe
{
	using Pipeline_OpenGL4_6 = Pipeline_OpenGL4_6_Windows;
}

#else
#warning "Opengl 4.6 not implemented for this OS!"

#endif

#endif