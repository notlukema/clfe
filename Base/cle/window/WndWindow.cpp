#include "WndWindow.h"

#include <cstdlib>
#include <iostream>
#include "../utils/StringUtils.h"

namespace cle {
	LRESULT CALLBACK WndWindow::WndProcWrapper(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		WndWindow* window;
		if (uMsg == WM_NCCREATE) {
			// Retrieve pointer to wrapper class from additional application data
			CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
			window = (WndWindow*)createStruct->lpCreateParams;

			// Store pointer to wrapper class in window's user data
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		}
		else {
			// Retrieve pointer to wrapper class from window's user data
			window = (WndWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (window) {
			return window->WndProc(hwnd, uMsg, wParam, lParam);
		}
		else { // Shouldn't happen
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	LRESULT CALLBACK WndWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case 0:
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	const WCHAR* WndWindow::GenClassName(long id) {
		// temporary
		std::string a = "CLE:" + std::to_string(id);
		return toWChar(a.c_str());
	}

	// Less complicated instance data

	WndWindow::WndWindow(int x, int y, int width, int height, const CHAR* name, long id, WNDPROC wndproc) : Window(id) {
		HINSTANCE hInstance = GetModuleHandle(NULL);
		const WCHAR* nameW = toWChar(name);

		active_ = false;

		className = GenClassName(id);
		std::wcout << L"Registering class: " << className << std::endl;

		WNDCLASS wc = { };
		wc.lpfnWndProc = wndproc;
		wc.hInstance = hInstance;
		wc.lpszClassName = className;

		class_ = RegisterClass(&wc);
		if (class_ == 0) {
			DWORD error = GetLastError();
			printf("Error registering class: %lu\n", error);
			return; // For now. I will set up a different class registertion system later.
		}

		// Create the window.

		hwnd_ = CreateWindowEx(
			0,
			MAKEINTATOM(class_),
			nameW,
			WS_OVERLAPPEDWINDOW,

			x, y, width, height,

			NULL,       // Parent window    
			NULL,       // Menu
			hInstance,  // Instance handle
			this        // Store current instance in user data
		);

		if (hwnd_ == NULL)
		{
			DWORD errorCode = GetLastError();
			std::wcerr << L"CreateWindowEx failed with error code: " << errorCode << std::endl;
			return;
		}

		active_ = true;
		ShowWindow(hwnd_, SW_SHOWNORMAL);
	}

	bool WndWindow::isActive() const {
		return active_;
	}

	bool WndWindow::isVisible() const {
		return IsWindowVisible(hwnd_);
	}

	const char* WndWindow::name() const {
		int len = GetWindowTextLengthA(hwnd_);
		if (len > 0) {
			char* buffer = new char[len + 1];
			GetWindowTextA(hwnd_, buffer, len + 1);
			return buffer;
		}
		return "";
	}

	const wchar_t* WndWindow::wname() const {
		int len = GetWindowTextLengthW(hwnd_);
		if (len > 0) {
			wchar_t* buffer = new wchar_t[len + 1];
			GetWindowTextW(hwnd_, buffer, len + 1);
			return buffer;
		}
		return L"";
	}


	int WndWindow::x() const {
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.left;
	}

	int WndWindow::y() const {
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.top;
	}

	int WndWindow::width() const {
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.right - rect.left;
	}

	int WndWindow::height() const {
		RECT rect;
		GetWindowRect(hwnd_, &rect);
		return rect.bottom - rect.top;
	}

	void WndWindow::x(int x) {
	}

	void WndWindow::y(int y) {

	}

	void WndWindow::width(int width) {

	}

	void WndWindow::height(int height) {
	}

	void WndWindow::show() {
		ShowWindow(hwnd_, SW_SHOW);
	}

	void WndWindow::hide() {
		ShowWindow(hwnd_, SW_HIDE);
	}

	WndWindow::~WndWindow() {
		active_ = false;
		DestroyWindow(hwnd_);
		UnregisterClassW(MAKEINTATOM(class_), GetModuleHandle(NULL));
	}

}