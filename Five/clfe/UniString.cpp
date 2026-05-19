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

	UniString::~UniString()
	{
		deleteData();
	}

#define UNISTR_BASE_STR str_char // Just for some "transparency"

	void UniString::deleteData()
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

	UniString& UniString::fill()
	{
		get_char();
		get_wchar_t();
		return *this;
	}

	const char* UniString::get_char() const
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

	const wchar_t* UniString::get_wchar_t() const
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

	UniString& UniString::operator=(const UniString& str)
	{
		if (this == &str)
		{
			return *this;
		}
		deleteData();

		len_ = str.len_;
		str_char = str.str_char == nullptr ? nullptr : copyStr(str.str_char);
		str_wchar_t = str.str_wchar_t == nullptr ? nullptr : copyStr(str.str_wchar_t);

		return *this;
	}

	UniString& UniString::operator=(UniString&& str) noexcept
	{
		if (this == &str)
		{
			return *this;
		}
		deleteData();

		len_ = str.len_;
		str_char = str.str_char;
		str_wchar_t = str.str_wchar_t;

		str.len_ = 0;
		str.str_char = nullptr;
		str.str_wchar_t = nullptr;

		return *this;
	}

	UniString::operator const char* () const
	{
		return get_char();
	}

	UniString::operator const wchar_t* () const
	{
		return get_wchar_t();
	}

	UniString operator+(const UniString& str1, const UniString& str2)
	{
		return UniString(concatStr(str1.str_char, str2.str_char));
	}

}