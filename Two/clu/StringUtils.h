#ifndef CLU_STRINGUTILS_H
#define CLU_STRINGUTILS_H

namespace clu
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

	const char* copyNarrow(const char* str);
	const wchar_t* copyWide(const wchar_t* str);

	inline const char* copyStr(const char* str)
	{
		return copyNarrow(str);
	}

}

#endif