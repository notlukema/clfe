#ifndef CLFE_UNISTRING_H
#define CLFE_UNISTRING_H

#include "../../clu/StringUtils.h"

#include <type_traits>

namespace clfe
{

	template <typename T>
		requires std::is_same_v<T, char> || std::is_same_v<T, wchar_t> // Only for char and wchar_t for now
	class UniString
	{
	private:
		T* str;

	public:
		UniString(const T* inputStr) : str{ copy(inputStr) }
		{
		}

		~UniString()
		{
			free(str);
		}

		const T* get() const
		{
			return str;
		}



	};

}

#endif