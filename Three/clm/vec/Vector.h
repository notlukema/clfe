#ifndef CLM_VECTOR_H
#define CLM_VECTOR_H

#include "../VecMatCommon.h"

namespace clfe
{

	template <msize_t Size, typename T>
	class Vector
	{
	protected:
		T array[Size];

	public:
		Vector() : array{} {}

		Vector(T scalar) requires (Size > 1)
		{
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = scalar;
			}
		}

		template <typename... Args>
			requires (sizeof...(Args) == Size) && AllCompatible<T, Args...>
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr)
		{
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = arr[i];
			}
		}

		Vector(const Vector<Size, T>& vec)
		{
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = vec.array[i];
			}
		}

		inline msize_t size() const
		{
			return Size;
		}

		inline T& operator[](msize_t i)
		{
			return array[i];
		}

		inline const T* get() const
		{
			return static_cast<const T*>(array);
		}

		inline T get(msize_t i) const
		{
			return array[i];
		}

		inline void setAt(msize_t i, T value)
		{
			array[i] = value;
		}

		template <typename U = T>
		U distance() const requires Arithmetic2<T, U>
		{
			T sum = static_cast<T>(0);
			for (msize_t i = 0; i < Size; i++)
			{
				sum += array[i] * array[i];
			}
			return static_cast<U>(sqrt(static_cast<U>(sum)));
		}

		template <typename U = T>
		Vector<Size, U> normalized() const requires Arithmetic2<T, U>
		{
			T dist = distance<T>();
			Vector<Size, U> result;
			for (msize_t i = 0; i < Size; i++)
			{
				result.array[i] = static_cast<U>(array[i] / dist);
			}
			return result;
		}

		Vector<Size, T>& normalize() requires Arithmetic<T>
		{
			T dist = distance<T>();
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = array[i] / dist;
			}
			return *this;
		}

	};

}

namespace clfe // Utility functions
{
	/*
	template <msize_t Size1, msize_t Size2, typename T>
	Vector<Size1, T> swap(const Vector<Size2, T>& vec) requires (Size1 != Size2)
	{
		return swapImpl<Size1, T>(vec, std::make_index_sequence<Size1>{});
	}

	template <msize_t Size, typename T, size_t... I>
	inline Vector<Size, T> swapImpl(const Vector<Size, T>& vec, std::index_sequence<I...>)
	{
		return Vector<Size, T>(vec.array[I]...);
	}
	*/

}

#include "VecOp.h"
#ifdef CLM_MATRIX_H
#include "../VecMatOp.h"
#endif

#endif