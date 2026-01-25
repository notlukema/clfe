#ifndef CLU_STRINGUTILS_H
#define CLU_STRINGUTILS_H

namespace clfe
{
	// All functions return a fresh copy of the string allocated on dynamic memory

	const char* toNarrowString(const wchar_t* wstr);
	const wchar_t* toWideString(const char* str);

	const char* concatNarrow(const char* str1, const char* str2);
	const wchar_t* concatWide(const wchar_t* str1, const wchar_t* str2);

	inline const char* concat(const char* str1, const char* str2)
	{
		return concatNarrow(str1, str2);
	}

	char* copyNarrow(const char* str);
	wchar_t* copyWide(const wchar_t* str);

	inline char* copy(const char* str)
	{
		return copyNarrow(str);
	}

	inline wchar_t* copy(const wchar_t* str)
	{
		return copyWide(str);
	}

	// Special

	template <typename To, typename From>
		requires false // Always false, to trigger specialization
	To* convertString(const From* str)
	{
		
	}

}

#include "ManyConvertString.h"

#endif