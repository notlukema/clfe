#include "Window.h"

#include "clfe/AttachmentLayers.h"
#include "clfe/InstanceTypes.h"

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
	InstanceList<Window>* Window::WindowsList = nullptr;

	InstanceListWrapper<Window>* Window::getWindowsList()
	{
		return WindowsList->getWrapper();
	}

	bool Window::init()
	{
		WindowsList = new InstanceList<Window>(InstanceTypes::Window);

		return true;
	}

	void Window::step(float delf, double deld)
	{
		for (Window* window : *WindowsList)
		{
			window->getInput()->step();
		}
	}

	void Window::terminate()
	{
		WindowsList->deepDelete();
		delete WindowsList;
		WindowsList = nullptr;
	}

	Window::Window(clid id) : thisid(id)
	{
		WindowsList->add(id, this);
		inputCore = new InputCore();
	}

	Window::~Window()
	{
		WindowsList->remove(thisid);
		delete inputCore;
	}

	clid Window::getID() const
	{
		return thisid;
	}

	InputCore* Window::getInput() const
	{
		return inputCore;
	}

}