#ifndef CLE_H
#define CLE_H

#ifndef CLE_CROSSPLATFORM_H
#include "CrossPlatform.h"
#endif

#ifndef CLE_ERROR_H
#include "Errors.h"
#endif


namespace cle {
	void init() {
#ifdef CLE_WINDOW_H
		cle::Window::init();
#endif
	}
}

#endif