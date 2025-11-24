#include "Window.h"

// ARTIFACT1: Should already be included by System.h and Window.h
#include "../../clfe/CrossPlatform.h"

namespace clfe
{

	Window* createWindow(int x, int y, int width, int height, const char* name) {
#ifdef CLFE_OS_WIN
		return new WinWnd(x, y, width, height, name);
#elif
		return nullptr;
#endif
	}

	Window* createWindow(int x, int y, int width, int height, const wchar_t* name) {
#ifdef CLFE_OS_WIN
		return new WinWnd(x, y, width, height, name);
#elif
		return nullptr;
#endif
	}

	Window::Window()
	{
		// Something here?
	}

	Window::~Window()
	{
		destroy();
	}

	void Window::terminate()
	{

	}

}