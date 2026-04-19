#include "UniString.h"

#include "clu/StringUtils.h"

namespace clfe
{

	UniString::UniString(const char* str) : str_char(nullptr), str_wchar_t(nullptr)
	{
		str_char = copyStrNarrow(str);
	}

	UniString::UniString(const wchar_t* str) : str_char(nullptr), str_wchar_t(nullptr)
	{
		str_char = toStrNarrow(str);
		str_wchar_t = copyStrWide(str);
	}

	UniString::~UniString()
	{
		if (str_char != nullptr)
		{
			delete str_char;
		}
		if (str_wchar_t != nullptr)
		{
			delete str_wchar_t;
		}
	}

#define UNISTR_BASE_STR str_char // just for some "transparency" or whatever

	const char* UniString::get_char()
	{
		if (str_char == nullptr)
		{
			str_char = toStrNarrow(UNISTR_BASE_STR);
		}
		return str_char;
	}

	const wchar_t* UniString::get_wchar_t()
	{
		if (str_wchar_t == nullptr)
		{
			str_wchar_t = toStrWide(UNISTR_BASE_STR);
		}
		return str_wchar_t;
	}

}