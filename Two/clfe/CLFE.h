#ifndef CLFE_CLFE_H
#define CLFE_CLFE_H

// Ties togethor the init, step, and terminate functions of various modules

namespace clfe
{

	bool init()
	{
		bool success = true;

#ifdef CLFE_SYSTEM_H
		System::init();
#endif

#ifdef CLFE_WINWND_H
		WinWnd::init();
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
		WinWnd::terminate();
		WinClass::terminate();
#endif
#ifdef CLFE_WINDOW_H

#endif
	}

}

#endif