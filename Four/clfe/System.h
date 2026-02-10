#ifndef CLFE_SYSTEM_H
#define CLFE_SYSTEM_H

#include "CrossPlatform.h"
#include "Error.h"
#include "CLFE.h"

using clid = unsigned int;

#ifdef CLU_USEWIDESTRING // check
using clchar = wchar_t;
#else
using clchar = char;
#endif

namespace clfe
{

	class System
	{
	private:
		static Attachment systemAttachment;
		static clid nextID;

	public:
		static bool init();
		static clid genNextID();

		// create recording system to record these ids and associated names

	};

}

#endif