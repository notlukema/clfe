#ifndef CLFE_SYSTEM_H
#define CLFE_SYSTEM_H

#include "CrossPlatform.h"
#include "Error.h"

using clid = unsigned int;

#ifdef CLU_USEWIDESTRING
using clchar = wchar_t;
#else
using clchar = char;
#endif

namespace clfe
{

	class System
	{
	private:
		static clid nextID;

	public:
		static void init();
		static clid genNextID();

		// create recording system to record these ids and associated names

	};

}

#endif