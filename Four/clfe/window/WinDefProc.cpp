#include "WinWnd.h"

#include "clfe/input/KeyTables.h"
#include "clfe/Log.h"

namespace clfe
{

	static const LRESULT BlankReturn = 0;

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
				window->getInput()->trigKeyDown(KeyTables::translateKey<WindowsKeys>(wParam));
				return BlankReturn;
			}
			if (uMsg == WM_KEYUP)
			{
				window->getInput()->trigKeyUp(KeyTables::translateKey<WindowsKeys>(wParam));
				return BlankReturn;
			}

			if (uMsg == WM_CLOSE)
			{
				window->destroy();
				return BlankReturn;
			}

			if (uMsg == WM_MOVE)
			{
				CLFE_LOG("moved");
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