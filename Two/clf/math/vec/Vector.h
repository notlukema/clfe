#ifndef CLFE_VECTOR_H
#define CLFE_VECTOR_H

#include "../VecMatCommon.h"

namespace clfe
{

	template <msize_t Size, typename T, typename P = lowp>
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

		template <msize_t Size1, typename P1>
			requires (Size1 <= Size)
		Vector(const Vector<Size1, T, P1>& vec) : array{ vec.array } {}

		template <msize_t Size1, typename P1>
			requires (Size1 > Size)
		Vector(const Vector<Size1, T, P1>& vec) : array{}
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

		P distance() const requires Arithmetic2<T, P>
		{
			P sum = static_cast<P>(0);
			for (msize_t i = 0; i < Size; i++)
			{
				sum += static_cast<P>(array[i] * array[i]);
			}
			return static_cast<P>(sqrt(sum));
		}

		P distSqr() const requires Arithmetic2<T, P>
		{
			P sum = static_cast<P>(0);
			for (msize_t i = 0; i < Size; i++)
			{
				sum += static_cast<P>(array[i] * array[i]);
			}
			return sum;
		}

		T nativeDist() const requires Arithmetic<T>
		{
			T sum = static_cast<T>(0);
			for (msize_t i = 0; i < Size; i++)
			{
				sum += array[i] * array[i];
			}
			return static_cast<T>(sqrt(sum));
		}

		T nativeDistSqr() const requires Arithmetic<T>
		{
			T sum = static_cast<T>(0);
			for (msize_t i = 0; i < Size; i++)
			{
				sum += array[i] * array[i];
			}
			return sum;
		}

		void normalize() requires Arithmetic<T>
		{
			T dist = nativeDist();
			for (msize_t i = 0; i < Size; i++)
			{
				array[i] = array[i] / dist;
			}
		}

		Vector<Size, P, P> normalized() const requires Arithmetic<T>
		{
			P dist = distance();
			Vector<Size, P, P> result;
			for (msize_t i = 0; i < Size; i++)
			{
				result.setAt(i, static_cast<P>(array[i]) / dist);
			}
			return result;
		}

	};

}

#include "VecOp.h"
#ifdef CLFE_MATRIX_H
#include "../VecMatOp.h"
#endif

#endif