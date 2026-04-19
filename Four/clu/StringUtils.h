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

	const char* toStrNarrow(const wchar_t* str);
	const wchar_t* toStrWide(const char* str);

	// Concatenation

	const char* concatStrNarrow(const char* str1, const char* str2);
	const wchar_t* concatStrWide(const wchar_t* str1, const wchar_t* str2);

	inline const char* concatStr(const char* str1, const char* str2)
	{
		return concatStrNarrow(str1, str2);
	}

	inline const wchar_t* concatStr(const wchar_t* str1, const wchar_t* str2)
	{
		return concatStrWide(str1, str2);
	}

	// Perhaps include inter-type string concatenation?

	// Copy

	char* copyStrNarrow(const char* str);
	wchar_t* copyStrWide(const wchar_t* str);

	inline char* copyStr(const char* str)
	{
		return copyStrNarrow(str);
	}

	inline wchar_t* copyStr(const wchar_t* str)
	{
		return copyStrWide(str);
	}

	// Flexible conversion functions

	inline const char* toStrNarrow(const char* str)
	{
		return copyStrNarrow(str);
	}

	inline const wchar_t* toStrWide(const wchar_t* str)
	{
		return toStrWide(str);
	}

	template <typename To, typename From>
		requires UtilsCompatibleString<To> && UtilsCompatibleString<From>
	const To* toStr(const From* str)
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