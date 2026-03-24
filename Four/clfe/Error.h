#ifndef CLFE_ERROR_H
#define CLFE_ERROR_H

#include <cstdio>

namespace clfe
{
	
	void inline logError(const char* message)
	{
		// For now, just print to console
		printf("CLFE Error: %s\n", message);
	}

}

#define CLFE_ERROR(msg) clfe::logError(msg)

#endif