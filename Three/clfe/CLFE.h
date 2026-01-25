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

#ifdef CLFE_INPUT_CENTRAL_H
		InputCentral::init();
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

#ifdef CLFE_WINDOW_H
		Window::step();
#endif

#ifdef CLFE_WINWND_H
		WinWnd::step();
#endif

#ifdef CLFE_INPUT_CENTRAL_H
		InputCentral::step();
#endif

		return success;
	}

	void terminate()
	{
#ifdef CLFE_WINDOW_H
		Window::terminate();
#endif

#ifdef CLFE_WINWND_H
		WinWnd::terminate();
		WinClass::terminate();
#endif

	}

}

#endif