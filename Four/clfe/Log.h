#ifndef CLFE_LOG_H
#define CLFE_LOG_H

#include "Exception.h"

#include <cstdio>

namespace clfe
{

	// very much a placeholder
	
	void inline logError(const char* message)
	{
		// For now, just print to console
		printf("CLFE Error: %s\n", message);
	}

	void inline logMsg(const char* message)
	{
		// For now, just print to console
		printf("CLFE Message: %s\n", message);
	}

	void inline runtimeError(const char* message)
	{
		throw RuntimeError(message);
	}

}

#define CLFE_ERROR(msg) clfe::logError(msg)
#define CLFE_LOG(msg) clfe::logMsg(msg)
#define CLFE_RUNTIME_ERROR(msg) clfe::runtimeError(msg)

#endif