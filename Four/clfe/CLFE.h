#ifndef CLFE_CLFE_H
#define CLFE_CLFE_H

// Ties togethor the init, step, and terminate functions of various modules

#include "Attachment.h"

#include <chrono>

namespace clfe
{

	bool init();
	void step(float dt);
	void step(double dt);
	void terminate();

	// Use own timer
	using Timer_t = std::chrono::steady_clock::time_point;
	extern Timer_t StepTimer;

	void resetTimer();
	float stepf();
	double stepd();

	inline float step()
	{
		return stepf();
	}

}

#endif