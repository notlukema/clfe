#include "WinWnd.h"

#include <Windows.h>

namespace clfe
{

	LRESULT CALLBACK WinWnd::defWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WinWnd* window;
		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
			window = (WinWnd*)createStruct->lpCreateParams;

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		}
		else {
			window = (WinWnd*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (window) {
			// TODO: replace with something more comprehensive
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		else { // Shouldn't happen
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

}