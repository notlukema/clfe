#include "Window_i.h"

#include "clfe/CrossPlatform.h"

#if defined(CLFE_OS_WIN)
#include "WinWnd.h"

#elif defined(CLFE_OS_MAC)
//#include "MacWnd.h"

#elif defined(CLFE_OS_LNX)
//#include "LnxWnd.h"

#else
#ifndef CLFE_SUPPRESS_WARNINGS
#warning "Windowing system not implemented by the engine for this OS!"
#endif

#endif


#ifndef CLFE_WINDOW_SUPPLEMENTAL_H
#define CLFE_WINDOW_SUPPLEMENTAL_H

namespace clfe
{

	inline Window* createWindow(UniString name, int x = WindowDefault, int y = WindowDefault, int width = WindowDefault, int height = WindowDefault)
	{
#if defined(CLFE_OS_WIN)
		return new WinWnd(name, x, y, width, height);
#elif defined(CLFE_OS_MAC)
		return nullptr;
#elif defined(CLFE_OS_LNX)
		return nullptr;
#else
		return nullptr;
#endif
	}

}

#endif