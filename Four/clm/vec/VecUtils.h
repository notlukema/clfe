#ifndef CLM_VECTOR_UTILS_H
#define CLM_VECTOR_UTILS_H

// Guards against if anyone decides to include this file directly
#include "Vector.h"

namespace clfe // Utility functions
{

	template <msize_t Size, msize_t Size0, typename T> // Could try replacing Size and Size0 with one template parameter
	inline Vector<Size, T> resize(const Vector<Size0, T>& vec) requires (Size == Size0)
	{
		return Vector<Size, T>(vec);
	}

	template <msize_t Size, msize_t Size0, typename T>
	Vector<Size, T> resize(const Vector<Size0, T>& vec) requires (Size != Size0)
	{
		Vector<Size, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, (i < Size0) ? vec.get(i) : static_cast<T>(0));
		}
		return result;
	}

	template <typename T, msize_t Size, typename U>
		requires Compatible<T, U>
	inline Vector<Size, T> cast(const Vector<Size, U>& vec)
	{
		return Vector<Size, T>(vec);
	}

}

#endif