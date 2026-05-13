#include "Window.h"

#include "clfe/AttachmentLayers.h"

#include "clfe/Log.h"

namespace clfe
{

	Window* createWindow(UniString name, int x, int y, int width, int height)
	{
#ifdef CLFE_OS_WIN
		return new WinWnd(name, x, y, width, height);
#elif
		return nullptr;
#endif
	}

	//

	const Attachment Window::WindowAttachment = Attachment(AttachmentLayers::Window, Window::init, Window::step, Window::terminate);
	InstanceList<Window>* Window::WindowList = nullptr;

	bool Window::init()
	{
		WindowList = new InstanceList<Window>();
		return true;
	}

	void Window::step(float delf, double deld)
	{
		for (Window* window : *WindowList)
		{
			window->getInput()->step();
		}
	}

	void Window::terminate()
	{
		delete WindowList;
		WindowList = nullptr;
	}

	Window::Window() : InstanceInterface(WindowList), exists_(true), destroyRequested(false),
		MoveCallback(nullptr), ResizeCallback(nullptr), CloseCallback(nullptr), MinimizeCallback(nullptr), MaximizeCallback(nullptr)//, VisibilityCallback(nullptr)
	{
		inputCore = new InputCore();
	}

	Window::~Window()
	{
		destroy();
		delete inputCore;
	}

	void Window::destroy()
	{
		if (exists_)
		{
			destroyRequested = true;
			if (CloseCallback != nullptr)
			{
				if (!CloseCallback())
				{
					return;
				}
			}

			innerDestroy();
			exists_ = false;
		}
	}

	void Window::hardDestroy()
	{
		if (exists_)
		{
			innerDestroy();
			exists_ = false;
			destroyRequested = true; // Might as well
		}
	}

	void Window::requestDestroy()
	{
		destroyRequested = true;
	}

	void Window::setCloseCallback(Function<bool()> callback)
	{
		CloseCallback = callback;
	}

	void Window::setMoveCallback(Function<void(int x, int y)> callback)
	{
		MoveCallback = callback;
	}

	void Window::setResizeCallback(Function<void(int width, int height)> callback)
	{
		ResizeCallback = callback;
	}
	/*
	void Window::setVisibilityCallback(Function<void(bool visible)> callback)
	{
		VisiblityCallback = callback;
	}
	*/
	void Window::setMinimizeCallback(Function<bool(bool minimized)> callback)
	{
		MinimizeCallback = callback;
	}

	void Window::setMaximizeCallback(Function<bool(bool maximized)> callback)
	{
		MaximizeCallback = callback;
	}

}