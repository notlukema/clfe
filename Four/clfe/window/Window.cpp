#include "Window.h"

#include "../InstanceTypes.h"

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

	const Attachment Window::WindowAttachment = Attachment(AttachmentLayers::Window, Window::init, Window::step, Window::terminate);
	InstanceList<Window>* Window::WindowsList = new InstanceList<Window>(InstanceTypes::Window);

	Window::Window(clid id) : thisid(id)
	{
		WindowsList->add(id, this);
	}

	Window::~Window()
	{
		WindowsList->remove(thisid);
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

	clid Window::getID() const
	{
		return thisid;
	}

}