#include "WinWindow_i.h"

#include "clfe/Log.h"

#include "clfe/input/KeyTables.h"

namespace clfe
{

	static const LRESULT BlankReturn = 0;

	LRESULT CALLBACK WinWindow::defWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WinWindow* window = nullptr;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
			window = (WinWindow*)createStruct->lpCreateParams;

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		}
		else
		{
			window = (WinWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (window == nullptr)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

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

}