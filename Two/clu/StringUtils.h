#ifndef CLU_STRINGUTILS_H
#define CLU_STRINGUTILS_H

namespace clu
{

	const wchar_t* toWideString(const char* str);
	const char* toNarrowString(const wchar_t* wstr);

}

#endif