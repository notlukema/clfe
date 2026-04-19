#ifndef CLFE_UNISTRING_H
#define CLFE_UNISTRING_H

#include "TypeTraits.h"

namespace clfe
{

	// Invented to solve different string type issues
	class UniString
	{
	private:
		const char* str_char; // The basic char is the common interface of UniString
		const wchar_t* str_wchar_t;

	public:
		UniString(const char* str);
		UniString(const wchar_t* str);
		~UniString();

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

		// put operations here soon + utility functions
		// consider = operations and move semantics

	};

}

#endif