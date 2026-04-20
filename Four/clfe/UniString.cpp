#include "UniString.h"

#include "clu/StringUtils.h"

namespace clfe
{

	UniString::UniString(const char* str) : len_(0), str_char(nullptr), str_wchar_t(nullptr)
	{
		str_char = copyStr(str);
		len_ = strLen(str_char);
	}

	UniString::UniString(const wchar_t* str) : len_(0), str_char(nullptr), str_wchar_t(nullptr)
	{
		str_char = toStrNarrow(str);
		str_wchar_t = copyStr(str);
		len_ = strLen(str_char);
	}

	UniString::UniString(const UniString& str) : len_(0), str_char(nullptr), str_wchar_t(nullptr)
	{
		str_char = copyStr(str.str_char);
		len_ = strLen(str_char);
	}

	UniString::UniString(UniString&& str) noexcept : len_(str.len_), str_char(str.str_char), str_wchar_t(str.str_wchar_t)
	{
		str.len_ = 0;
		str.str_char = nullptr;
		str.str_wchar_t = nullptr;
	}

#define UNISTR_BASE_STR str_char // just for some "transparency" or whatever

	static void deleteData(UniString& str)
	{
		if (str.str_char != nullptr)
		{
			delete str.str_char;
		}
		if (str.str_wchar_t != nullptr)
		{
			delete str.str_wchar_t;
		}
	}

	UniString::~UniString()
	{
		deleteData(*this);
	}

	const char* UniString::get_char()
	{
		if (str_char == nullptr)
		{
			if (UNISTR_BASE_STR == nullptr)
			{
				return nullptr;
			}
			str_char = toStrNarrow(UNISTR_BASE_STR);
		}
		return str_char;
	}

	const wchar_t* UniString::get_wchar_t()
	{
		if (str_wchar_t == nullptr)
		{
			if (UNISTR_BASE_STR == nullptr)
			{
				return nullptr;
			}
			str_wchar_t = toStrWide(UNISTR_BASE_STR);
		}
		return str_wchar_t;
	}

	// Utility

	UniString::operator bool() const
	{
		return len_ > 0;
	}

	UniString& UniString::operator=(UniString&& str) noexcept
	{
		if (this == &str)
		{
			return *this;
		}
		deleteData(*this);

		len_ = str.len_;
		str_char = str.str_char;
		str_wchar_t = str.str_wchar_t;

		str.len_ = 0;
		str.str_char = nullptr;
		str.str_wchar_t = nullptr;

		return *this;
	}

	UniString UniString::operator+(const UniString& str)
	{
		return UniString(concatStr(str_char, str.str_char));
	}

}