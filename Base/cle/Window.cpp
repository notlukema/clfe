#include "Window.h"

#include <cstdlib>
#include <vector>
#include <iostream>

namespace cle {
	const WCHAR* Window::toWChar(const CHAR* str) {
		// Obtain required size of new wide string
        size_t required_size;
        errno_t err = mbstowcs_s(&required_size, NULL, 0, str, _TRUNCATE);
		if (err != 0) {
			printf("Error determining required size: %d\n", err);
			return nullptr;
		}

		// Initialize buffer of required size
		WCHAR* buffer = (WCHAR*)malloc(required_size * sizeof(WCHAR));

		// Convert to wide string
		err = mbstowcs_s(nullptr, buffer, required_size, str, _TRUNCATE);
		if (err != 0) {
			printf("Error converting string: %d\n", err);
			return nullptr;
		}

		return buffer;
	}

	Window::Window(int x, int y, int width, int height, std::string name) {
		Window(x, y, width, height, toWChar(name.c_str()));
	}

	Window::Window(int x, int y, int width, int height, std::wstring name) {
		Window(x, y, width, height, name.c_str());
	}

	Window::Window(int x, int y, int width, int height, const CHAR* name) {
		Window(x, y, width, height, toWChar(name));
	}

	Window::Window(int x, int y, int width, int height, const WCHAR* name) {
		HINSTANCE hInstance = GetModuleHandle(NULL);

		const WCHAR th[] = L"bruh";

		WNDCLASS wc = { };

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = th;

		RegisterClass(&wc);

		// Create the window.

		hwnd = CreateWindowEx(
			0,                              // Optional window styles.
			th,                             // Window class
			name,                           // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,       // Parent window    
			NULL,       // Menu
			hInstance,  // Instance handle
			NULL        // Additional application data
		);

		if (hwnd == NULL)
		{
			return;
		}

		ShowWindow(hwnd, SW_SHOW);
	}

	HWND Window::gethwnd() const {
		return Window::hwnd;
	}

	bool Window::isActive() const {
		return active;
	}
}