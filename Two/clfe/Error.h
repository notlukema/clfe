#ifndef CLFE_ERROR_H
#define CLFE_ERROR_H

#include <cstdio>

namespace cle
{

	void inline logError(const char* message)
	{
		// For now, just print to console
		printf("CLFE Error: %s\n", message);
	}

}

#endif