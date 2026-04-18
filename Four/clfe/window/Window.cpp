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

	//

	const Attachment Window::WindowAttachment = Attachment(AttachmentLayers::Window, Window::init, Window::step, Window::terminate);
	InstanceList<Window>* Window::WindowsList = nullptr;

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
		delete WindowsList;
		WindowsList = nullptr;
	}

	Window::Window() : InstanceInterface(WindowsList), exists_(true), destroyRequested(false),
		MoveCallback(nullptr), ResizeCallback(nullptr), CloseCallback(nullptr), MinimizeCallback(nullptr), MaximizeCallback(nullptr)//, VisibilityCallback(nullptr)
	{
		inputCore = new InputCore();
	}

	Window::~Window()
	{
		destroy();
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