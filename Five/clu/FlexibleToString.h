#ifndef CLU_FLEXIBLETOSTRING_H
#define CLU_FLEXIBLETOSTRING_H

#include "clfe/UniString.h"

#include <sstream>
#include <string>

namespace clfe
{

	template <typename... Args>
	UniString toStr(Args... args)
	{
		std::stringstream ss;
		(ss << ... << args);
		std::string str = ss.str();
		return UniString(str.c_str());
	}

}

#endif