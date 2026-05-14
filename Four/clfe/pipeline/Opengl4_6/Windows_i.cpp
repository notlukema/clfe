#include "Windows_i.h"

namespace clfe
{

	void GL4_6_Extension_Windows::attachWindow(GL4_6_Extension_Windows* this_, WinWnd* window)
	{
		// Do nothing for now
	}

	void GL4_6_Extension_Windows::detachWindow(GL4_6_Extension_Windows* this_, WinWnd* window)
	{
		// Do nothing for now
	}

	GL4_6_Extension_Windows::GL4_6_Extension_Windows() : pool(this, attachWindow, detachWindow)
	{
		//initWindow(nullptr, nullptr);
	}

	bool GL4_6_Extension_Windows::compatible(Window* window)
	{
		return dynamic_cast<WinWnd*>(window) != nullptr;
	}

	bool GL4_6_Extension_Windows::initWindow(Window* window)
	{
		WinWnd* winwnd = dynamic_cast<WinWnd*>(window);
		if (winwnd == nullptr)
		{
			return false;
		}

		return true;
	};

}