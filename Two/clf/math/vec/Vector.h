#ifndef CLFE_VECTOR_H
#define CLFE_VECTOR_H

#include <type_traits>

namespace clfe
{

	using lowp = float;
	using mediump = double;
	using highp = long double;

	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <typename T, typename P>
	concept Arithmetic2 = std::is_arithmetic_v<T> && std::is_arithmetic_v<P> && std::is_convertible_v<T, P>;

	template <int Size, typename T, typename P = lowp>
		requires (Size > 0)
	class Vector
	{
	protected:
		T array[Size];

	public:
		template <typename... Args>
			requires (sizeof...(Args) <= Size)
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		template <typename P1>
		Vector(const Vector<Size, T, P1>& vec) : array{}
		{
			for (int i = 0; i < Size; i++)
			{
				array[i] = vec.get(i);
			}
		}

		template <int Size1, typename P1>
			requires (Size1 > 0) && (Size1 != Size)
		Vector(const Vector<Size1, T, P1>& vec) : array{}
		{
			int minSize = (Size < Size1) ? Size : Size1;
			for (int i = 0; i < minSize; i++)
			{
				array[i] = vec.get(i);
			}
			for (int i = minSize; i < Size; i++)
			{
				array[i] = static_cast<T>(0);
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
			for (int i = 0; i < Size; i++)
			{
				sum += static_cast<P>(array[i] * array[i]);
			}
			return static_cast<P>(sqrt(sum));
		}

		P distSqr() const requires Arithmetic2<T, P>
		{
			P sum = static_cast<P>(0);
			for (int i = 0; i < Size; i++)
			{
				sum += static_cast<P>(array[i] * array[i]);
			}
			return sum;
		}

		T nativeDist() const requires Arithmetic<T>
		{
			T sum = static_cast<T>(0);
			for (int i = 0; i < Size; i++)
			{
				sum += array[i] * array[i];
			}
			return static_cast<T>(sqrt(sum));
		}

		T nativeDistSqr() const requires Arithmetic<T>
		{
			T sum = static_cast<T>(0);
			for (int i = 0; i < Size; i++)
			{
				sum += array[i] * array[i];
			}
			return sum;
		}

		void normalize() requires Arithmetic<T>
		{
			T dist = nativeDist();
			for (int i = 0; i < Size; i++)
			{
				array[i] = array[i] / dist;
			}
		}

		Vector<Size, P, P> normalized() const requires Arithmetic<T>
		{
			P dist = distance();
			Vector<Size, P, P> result;
			for (int i = 0; i < Size; i++)
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