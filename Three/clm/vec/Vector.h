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
		template <typename... Args>
			requires (sizeof...(Args) <= Size)
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : array{}
		{
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = arr[i];
			}
		}

		template <msize_t Size1>
			requires (Size1 <= Size)
		Vector(const Vector<Size1, T>& vec) : array{ vec.array } {}

		template <msize_t Size1>
			requires (Size1 > Size)
		Vector(const Vector<Size1, T>& vec) : array{}
		{
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = vec.get(i);
			}
		}

		inline int size() const
		{
			return Size;
		}

		inline T& operator[](int i)
		{
			return array[i];
		}

		inline const T* get() const
		{
			return static_cast<const T*>(array);
		}

		inline T get(int i) const
		{
			return array[i];
		}

		inline void setAt(int i, T value)
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

#include "VecOp.h"
#ifdef CLM_MATRIX_H
#include "../VecMatOp.h"
#endif

#endif