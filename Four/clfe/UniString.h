#ifndef CLFE_UNISTRING_H
#define CLFE_UNISTRING_H

#include "TypeTraits.h"

namespace clfe
{

	// Invented to solve different string type issues
	class UniString
	{
	private:
		size_t len_;
		char* str_char; // The basic char is the common interface of UniString
		wchar_t* str_wchar_t;

		friend void deleteData(UniString& str);

	public:
		UniString(const char* str);
		UniString(const wchar_t* str);

		UniString(const UniString& str);
		UniString(UniString&& str) noexcept;
		~UniString();

		inline size_t length() const
		{
			return len_;
		}

		inline int len() const
		{
			return static_cast<int>(len_);
		}

		const char* get_char();
		const wchar_t* get_wchar_t();

		template <typename T>
		const T* get()
		{
			if (IsSame<T, char>)
			{
				return get_char();
			}
			if (IsSame<T, wchar_t>)
			{
				return get_wchar_t();
			}
			return nullptr;
		}

		// Utility

		explicit operator bool() const;

		UniString& operator=(const UniString& str);
		UniString& operator=(UniString&& str) noexcept;

		friend UniString operator+(const UniString& str1, const UniString& str2);

	};

	UniString operator+(const UniString& str1, const UniString& str2);

}

#endif