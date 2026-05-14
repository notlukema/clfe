#include "Windows_i.h"

#include "glad/glad.h"

namespace clfe
{

	bool GL4_6_Extension_Windows::attachWindow(GL4_6_Extension_Windows* this_, WinWnd* window)
	{
		// Default pixel format descriptor
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),  // Size Of This Pixel Format Descriptor
			1,                              // Version Number
			PFD_DRAW_TO_WINDOW |            // Format Must Support Window
			PFD_SUPPORT_OPENGL |            // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,               // Must Support Double Buffering
			PFD_TYPE_RGBA,                  // Request An RGBA Format
			32,                             // Select Our Color Depth
			0, 0, 0, 0, 0, 0,               // Color Bits Ignored
			0,                              // No Alpha Buffer
			0,                              // Shift Bit Ignored
			0,                              // No Accumulation Buffer
			0, 0, 0, 0,                     // Accumulation Bits Ignored
			24,                             // Z-Buffer Depth
			0,                              // No Stencil Buffer
			0,                              // No Auxiliary Buffer
			PFD_MAIN_PLANE,                 // Main Drawing Layer
			0,                              // Reserved
			0, 0, 0                         // Layer Masks Ignored
		};

		HDC hdc = window->getHDC();
		if (hdc == nullptr)
		{
			return false;
		}

		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if (pixelFormat == 0)
		{
			return false;
		}

		if (!SetPixelFormat(hdc, pixelFormat, &pfd))
		{
			return false;
		}

		// First initialization
		if (this_->hrc == nullptr)
		{
			this_->hrc = wglCreateContext(hdc);
			if (this_->hrc == nullptr)
			{
				return false;
			}

			if (!wglMakeCurrent(hdc, this_->hrc))
			{
				return false;
			}

			if (gladLoadGL() == 0)
			{
				return false;
			}
		}

		return true;
	}

	void GL4_6_Extension_Windows::detachWindow(GL4_6_Extension_Windows* this_, WinWnd* window)
	{
		if (wglGetCurrentDC() == window->getHDC())
		{
			wglMakeCurrent(nullptr, nullptr);
		}
	}

	GL4_6_Extension_Windows::GL4_6_Extension_Windows() : pool(this, attachWindow, detachWindow), hrc(nullptr)
	{}

	GL4_6_Extension_Windows::~GL4_6_Extension_Windows()
	{
		pool.releaseAll();
		if (hrc != nullptr)
		{
			wglDeleteContext(hrc);
		}
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

		return pool.attach(winwnd->pullLink());
	};

	bool GL4_6_Extension_Windows::makeCurrent(Window* window)
	{
		if (hrc == nullptr)
		{
			return false;
		}

		if (window == nullptr)
		{
			window = pool.first();
			if (window == nullptr)
			{
				return false;
			}
		}

		WinWnd* winwnd = dynamic_cast<WinWnd*>(window);
		if (winwnd == nullptr)
		{
			return false;
		}

		if (!pool.contains(winwnd))
		{
			return false;
		}

		HDC hdc = winwnd->getHDC();

		if (hdc == nullptr)
		{
			return false;
		}

		if (wglGetCurrentDC() == hdc)
		{
			return true;
		}

		return wglMakeCurrent(hdc, hrc);
	}

}