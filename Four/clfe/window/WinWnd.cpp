#include "WinWnd.h"

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

	void WinWnd::innerDestroy()
	{
		// Detach from pipelines: delete mutuallinks
		DestroyWindow(hwnd_);
	}

	int WinWnd::getX() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.left;
	}

	int WinWnd::getY() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.top;
	}

	Vector2i WinWnd::getPosition() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return Vector2i(rect.left, rect.top);
	}

	void WinWnd::setX(int x)
	{
		SetWindowPos(hwnd_, NULL, x, getY(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void WinWnd::setY(int y)
	{
		SetWindowPos(hwnd_, NULL, getX(), y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void WinWnd::setPosition(int x, int y)
	{
		SetWindowPos(hwnd_, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void WinWnd::setPosition(const Vector2i& pos)
	{
		SetWindowPos(hwnd_, NULL, pos.x(), pos.y(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
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

	Vector2i WinWnd::getSize() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return Vector2i(rect.right - rect.left, rect.bottom - rect.top);
	}

	void WinWnd::setWidth(int width)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, width, getHeight(), SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWnd::setHeight(int height)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, getWidth(), height, SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWnd::setSize(int width, int height)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWnd::setSize(const Vector2i& size)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, size.x(), size.y(), SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWnd::show()
	{
		ShowWindow(hwnd_, SW_SHOW);
	}

	void WinWnd::hide()
	{
		ShowWindow(hwnd_, SW_HIDE);
	}

	void WinWnd::setVisible(bool visible)
	{
		ShowWindow(hwnd_, visible ? SW_SHOW : SW_HIDE);
	}

	bool WinWnd::isVisible()
	{
		return true;
	}

	void WinWnd::minimize()
	{

	}

	void WinWnd::unminimize()
	{

	}

	void WinWnd::setMinimized(bool minimize)
	{

	}

	bool WinWnd::isMinimized()
	{
		return false;
	}

	void WinWnd::maximize()
	{

	}

	void WinWnd::unmaximize()
	{

	}

	void WinWnd::setMaximized(bool maximize)
	{

	}

	bool WinWnd::isMaximized()
	{
		return false;
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