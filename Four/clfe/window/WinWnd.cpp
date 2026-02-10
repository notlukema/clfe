#include "WinWnd.h"

#include "../Error.h"

#include <Windows.h>

namespace clfe
{

	void WinWnd::step()
	{
		// TODO: consider threading and stuff and also improve algorithm
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	// Split section


	WinWnd::WinWnd(int x, int y, int width, int height, const char* name)
	{
		const WCHAR* wName = toWideString(name);
		createWindow(x, y, width, height, wName, WinClass::getDefaultClass());
		delete wName;
	}

	WinWnd::WinWnd(int x, int y, int width, int height, const WCHAR* name)
	{
		createWindow(x, y, width, height, name, WinClass::getDefaultClass());
	}

	WinWnd::WinWnd(int x, int y, int width, int height, const char* name, const WinClass* wClass)
	{
		const WCHAR* wName = toWideString(name);
		createWindow(x, y, width, height, wName, wClass);
		delete wName;
	}

	WinWnd::WinWnd(int x, int y, int width, int height, const WCHAR* name, const WinClass* wClass)
	{
		createWindow(x, y, width, height, name, wClass);
	}

	void WinWnd::createWindow(int x, int y, int width, int height, const WCHAR* name, const WinClass* wClass)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);

		// Handle defaults
		if (x < 0) {
			x = CW_USEDEFAULT;
		}
		if (y < 0) {
			y = CW_USEDEFAULT;
		}
		if (width < 0) {
			width = CW_USEDEFAULT;
		}
		if (height < 0) {
			height = CW_USEDEFAULT;
		}

		wClass_ = wClass;
		hwnd_ = CreateWindowExW(
			NULL,
			MAKEINTATOM(wClass->getClassAtom()),
			name,
			WS_OVERLAPPEDWINDOW,

			x, y, width, height,

			NULL,
			NULL,
			hInstance,
			this
		);

		if (hwnd_ == NULL)
		{
			DWORD errorCode = GetLastError();
			logError("Placeholder error, fix later!"); // TODO: fix error
			return;
		}

		ShowWindow(hwnd_, SW_SHOWNORMAL);
	}

	WinWnd::~WinWnd()
	{
		destroy();
	}

	HWND WinWnd::getHWND() const
	{
		return hwnd_;
	}

	bool WinWnd::exists() const
	{
		return true;
	}

	void WinWnd::destroy()
	{
	}

	int WinWnd::getX() const
	{
		return 0;
	}

	int WinWnd::getY() const
	{
		return 0;
	}

	int WinWnd::getWidth() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.right - rect.left;
	}

	int WinWnd::getHeight() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.bottom - rect.top;
	}

	void WinWnd::setX(int x)
	{
	}

	void WinWnd::setY(int y)
	{
	}

	void WinWnd::setWidth(int width)
	{
	}

	void WinWnd::setHeight(int height)
	{
	}

	void WinWnd::show()
	{
	}

	void WinWnd::hide()
	{
	}

	void WinWnd::setVisible(bool visible)
	{
	}

	bool WinWnd::isVisible()
	{
		return true;
	}

	const char* WinWnd::getNameNarrow()
	{
		return "";
	}

	const WCHAR* WinWnd::getNameWide()
	{
		return L"";
	}

	void WinWnd::setName(const char* name)
	{

	}

	void WinWnd::setName(const WCHAR* name)
	{
	}

	// Keep adding them

}