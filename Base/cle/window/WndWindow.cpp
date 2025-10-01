#if defined(_WIN32) || defined(_WIN64)
// Windows specific code definition for Window.h

#include "WndWindow.h"

#include <cstdlib>
#include <iostream>

namespace cle {
	LRESULT CALLBACK WndWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	WndWindow::WndWindow(int x, int y, int width, int height, std::string name) {
		WndWindow(x, y, width, height, toWChar(name.c_str()));
	}

	WndWindow::WndWindow(int x, int y, int width, int height, std::wstring name) {
		WndWindow(x, y, width, height, name.c_str());
	}

	WndWindow::WndWindow(int x, int y, int width, int height, const CHAR* name) {
		WndWindow(x, y, width, height, toWChar(name));
	}

	WndWindow::WndWindow(int x, int y, int width, int height, const WCHAR* name) {
		HINSTANCE hInstance = GetModuleHandle(NULL);

		// Note: create function to generate window class names
		//const WCHAR CLASS_NAME[] = L"Sample Window Class";
		const WCHAR* CLASS_NAME = toWChar(std::to_string(rand() % 100).c_str());
		std::wcout << L"Regsitering class: " << CLASS_NAME << std::endl;

		WNDCLASS wc = { };
		wc.lpfnWndProc = WndProcWrapper;
		wc.hInstance = hInstance;
		wc.lpszClassName = CLASS_NAME;

		ATOM atom = RegisterClass(&wc);
		if (atom == 0) {
			DWORD error = GetLastError();
			printf("Error registering class: %lu\n", error);
			return; // For now. I will set up a different class registertion system later.
		}

		// Create the window.

		hwnd = CreateWindowEx(
			0,                              // Optional window styles.
			CLASS_NAME,                     // Window class
			name,                           // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// Size and position
			x, y, width, height,

			NULL,       // Parent window    
			NULL,       // Menu
			hInstance,  // Instance handle
			this        // Store current instance in user data
		);

		if (hwnd == NULL)
		{
			DWORD errorCode = GetLastError();
			std::wcerr << L"CreateWindowEx failed with error code: " << errorCode << std::endl;
			return;
		}

		ShowWindow(hwnd, SW_SHOWNORMAL);
	}

	HWND WndWindow::gethwnd() const {
		return WndWindow::hwnd;
	}
}

#endif