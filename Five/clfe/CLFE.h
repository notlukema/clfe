#ifndef CLFE_CLFE_H
#define CLFE_CLFE_H

#include "Global.h"
#include "Allocation.h"

// Ties togethor the init, step, and terminate functions of various modules

namespace clfe
{

	bool init();
	bool init(const ApplicationInfo& applicationInfo);
	bool init(const Allocator& allocator);
	bool init(const ApplicationInfo& applicationInfo, const Allocator& allocator);

	void step(float dt);
	void step(double dt);

	void terminate();

	void resetTimer();
	float stepf();
	double stepd();

	inline float step()
	{
		return stepf();
	}

}

#endif