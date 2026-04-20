#ifndef CLU_STRINGUTILS_H
#define CLU_STRINGUTILS_H

#include "TypeTraits.h"

namespace clfe
{
	// All functions return a fresh copy of the string allocated on dynamic memory

	// Compatible strings with StringUtils and many other string-related things
	template <typename T>
	concept UtilsCompatibleString = IsSame<T, char> || IsSame<T, wchar_t>;

	// Convert

	char* toStrNarrow(const wchar_t* str);
	wchar_t* toStrWide(const char* str);

	// Concatenation

	char* concatStr(const char* str1, const char* str2);
	wchar_t* concatStr(const wchar_t* str1, const wchar_t* str2);

	// Perhaps include inter-type string concatenation?

	// Length

	size_t strLen(const char* str);
	size_t strLen(const wchar_t* str);

	// Copy

	char* copyStr(const char* str);
	wchar_t* copyStr(const wchar_t* str);

	// Cut

	char* cutStr(const char* str, size_t a, size_t b);
	wchar_t* cutStr(const wchar_t* str, size_t a, size_t b);

	// Flexible conversion functions

	inline char* toStrNarrow(const char* str)
	{
		return copyStr(str);
	}

	inline wchar_t* toStrWide(const wchar_t* str)
	{
		return copyStr(str);
	}

	template <typename To, typename From>
		requires UtilsCompatibleString<To> && UtilsCompatibleString<From>
	To* toStr(const From* str)
	{
		if (IsSame<To, char>)
		{
			if (IsSame<From, char>)
			{
				return copyStr(str);
			}
			return toStrNarrow(str);
		}
		if (IsSame<To, wchar_t>)
		{
			if (IsSame<From, wchar_t>)
			{
				return copyStr(str);
			}
			return toStrWide(str);
		}
		return nullptr;
	}

}

#endif