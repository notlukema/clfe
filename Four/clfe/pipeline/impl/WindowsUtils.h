#ifndef CLFE_WINDOWSUTILS_H
#define CLFE_WINDOWSUTILS_H

#include "PixelFormat.h"

#include <Windows.h>

namespace clfe
{

	struct WindowsUtils
	{

		static PIXELFORMATDESCRIPTOR convertToWindowsFormat(PixelFormat format)
		{
			return {
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
		}

	};

}

#endif