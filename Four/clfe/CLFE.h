#ifndef CLFE_CLFE_H
#define CLFE_CLFE_H

// Ties togethor the init, step, and terminate functions of various modules

namespace clfe
{

	bool init();
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