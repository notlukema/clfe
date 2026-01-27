#include "Window.h"

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

	Attachment Window::windowAttachment = Attachment(50, Window::init, Window::step, Window::terminate);

	Window::Window()
	{
		// Something here?
	}

	Window::~Window()
	{
	}

	bool Window::init()
	{
		return true;
	}

	void Window::step(float delf, double deld)
	{
	}

	void Window::terminate()
	{
	}

}