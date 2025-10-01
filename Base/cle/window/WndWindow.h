#ifndef CLE_WNDWINDOW_H
#define CLE_WNDWINDOW_H

#include "../Window.h"

#include <Windows.h>

#define WDEFAULT CW_USEDEFAULT

namespace cle {
	class WndWindow : public cle::Window {
	private:
		static LRESULT CALLBACK WndProcWrapper(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			WndWindow* window;
			if (uMsg == WM_NCCREATE) { // On create
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

		LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		HWND hwnd;
	public:
		const WCHAR* toWChar(const CHAR* str) {
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

		WndWindow(int x, int y, int width, int height, std::string name);
		WndWindow(int x, int y, int width, int height, std::wstring name);
		WndWindow(int x, int y, int width, int height, const CHAR* name);
		WndWindow(int x, int y, int width, int height, const WCHAR* name);
		HWND gethwnd() const;

		// create destructor to free items such as the name
	};
}

#endif