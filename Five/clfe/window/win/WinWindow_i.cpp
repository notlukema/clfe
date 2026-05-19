#include "WinWindow_i.h"

#include "clfe/Log.h"

namespace clfe
{

	void WinWindow::step()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//

	WinWindow::WinWindow(UniString name, int x, int y, int width, int height) : well(this)
	{
		createWindow(name, WinClass::getDefaultClass(), x, y, width, height);
	}

	WinWindow::WinWindow(UniString name, const WinClass* wClass, int x, int y, int width, int height) : well(this)
	{
		createWindow(name, wClass, x, y, width, height);
	}

	void WinWindow::createWindow(UniString name, const WinClass* wClass, int x, int y, int width, int height)
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
			name.get_wchar_t(),
			WS_OVERLAPPEDWINDOW,

			x, y, width, height,

			NULL,
			NULL,
			hInstance,
			this
		);

		if (hwnd_ == NULL)
		{
			//DWORD errorCode = GetLastError();
			CLFE_ERROR("Failed to create windows window!");
			return;
		}

		hdc_ = GetDC(hwnd_);

		if (hdc_ == NULL)
		{
			CLFE_ERROR("Failed to create window device!");
		}

		ShowWindow(hwnd_, SW_SHOWNORMAL);
	}

	WinWindow::~WinWindow()
	{
		innerDestroy();
	}

	void WinWindow::innerDestroy()
	{
		well.releaseAll();
		ReleaseDC(hwnd_, hdc_);
		DestroyWindow(hwnd_);
	}

	UniString WinWindow::getName()
	{
		return UniString("funky");
	}

	void WinWindow::setName(UniString name)
	{

	}

	int WinWindow::getX() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.left;
	}

	int WinWindow::getY() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.top;
	}

	Vector2i WinWindow::getPosition() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return Vector2i(rect.left, rect.top);
	}

	void WinWindow::setX(int x)
	{
		SetWindowPos(hwnd_, NULL, x, getY(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void WinWindow::setY(int y)
	{
		SetWindowPos(hwnd_, NULL, getX(), y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void WinWindow::setPosition(int x, int y)
	{
		SetWindowPos(hwnd_, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void WinWindow::setPosition(const Vector2i& pos)
	{
		SetWindowPos(hwnd_, NULL, pos.x(), pos.y(), 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	int WinWindow::getWidth() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.right - rect.left;
	}

	int WinWindow::getHeight() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.bottom - rect.top;
	}

	Vector2i WinWindow::getSize() const
	{
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return Vector2i(rect.right - rect.left, rect.bottom - rect.top);
	}

	void WinWindow::setWidth(int width)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, width, getHeight(), SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWindow::setHeight(int height)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, getWidth(), height, SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWindow::setSize(int width, int height)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWindow::setSize(const Vector2i& size)
	{
		SetWindowPos(hwnd_, NULL, 0, 0, size.x(), size.y(), SWP_NOZORDER | SWP_NOMOVE);
	}

	void WinWindow::show()
	{
		ShowWindow(hwnd_, SW_SHOW);
	}

	void WinWindow::hide()
	{
		ShowWindow(hwnd_, SW_HIDE);
	}

	void WinWindow::setVisible(bool visible)
	{
		ShowWindow(hwnd_, visible ? SW_SHOW : SW_HIDE);
	}

	bool WinWindow::isVisible()
	{
		return true;
	}

	void WinWindow::minimize()
	{

	}

	void WinWindow::unminimize()
	{

	}

	void WinWindow::setMinimized(bool minimize)
	{

	}

	bool WinWindow::isMinimized()
	{
		return false;
	}

	void WinWindow::maximize()
	{

	}

	void WinWindow::unmaximize()
	{

	}

	void WinWindow::setMaximized(bool maximize)
	{

	}

	bool WinWindow::isMaximized()
	{
		return false;
	}

	// Keep adding them

}