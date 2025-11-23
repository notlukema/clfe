#ifndef CLFE_CLFE_H
#define CLFE_CLFE_H

namespace clfe
{
	// Shouldn't be included in more than one source file so... fine to use non-inline functions?

	bool init()
	{
		bool success = true;

#ifdef CLFE_WINWND_H
		WinClass::init();
#endif

		return success;
	}

	bool step()
	{
		bool success = true;

#ifdef CLFE_WINWND_H
		WinWnd::step();
#endif

		return success;
	}

	void terminate()
	{
#ifdef CLFE_WINWND_H
		WinClass::terminate();
#endif
	}

}

#endif