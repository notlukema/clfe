#include "WinWnd.h"

#include <Windows.h>

namespace clfe
{

	LRESULT CALLBACK WinWnd::defWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WinWnd* window;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
			window = (WinWnd*)createStruct->lpCreateParams;

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		}
		else
		{
			window = (WinWnd*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (window)
		{
			if (uMsg == WM_KEYDOWN)
			{
				window->getInput()->trigKeyDown(KeyTable<WINDOWS_KEYS>::KeyMap[wParam]);
			}
			if (uMsg == WM_KEYUP)
			{
				window->getInput()->trigKeyUp(KeyTable<WINDOWS_KEYS>::KeyMap[wParam]);
			}

			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		else
		{ // Shouldn't happen
			CLFE_ERROR("");
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

}