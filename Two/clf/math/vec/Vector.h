#ifndef CLFE_VECTOR_H
#define CLFE_VECTOR_H

#include "../Math.h"

#include <type_traits>
#include <concepts>

namespace clfe
{

	using lowp = float;
	using mediump = double;
	using highp = long double;

	template <typename T>
	concept Arithmetic = std::is_arithmetic_v<T>;

	template <typename T, typename P>
	concept Arithmetic2 = std::is_arithmetic_v<T> && std::is_arithmetic_v<P> && std::is_convertible_v<T, P>;

	template <int Size, typename T, typename P = float>
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
			// The compiler should automatically unroll smaller loops... I think?
			for (int i = 0; i < Size; i++)
			{
				array[i] = vec.array[i];
			}
		}

		int size() const
		{
			return Size;
		}

		const T* get() const
		{
			return static_cast<const T*>(array);
		}

		T get(int i) const
		{
			return array[i];
		}

		void set(int i, T value)
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

		template <int Size0, typename T0, typename U0, typename P1, typename P2>
			requires (Size0 > 0) && Arithmetic<T0>&& Arithmetic<U0>
		friend auto dot(const Vector<Size0, T0, P1>& vec1, const Vector<Size0, U0, P2>& vec2) -> decltype(static_cast<T0>(0) + static_cast<U0>(0));

	};

	template <int Size, typename T, typename U, typename P1, typename P2>
		requires (Size > 0) && Arithmetic<T> && Arithmetic<U>
	auto dot(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> decltype(static_cast<T>(0) + static_cast<U>(0))
	{
		auto result = static_cast<decltype(static_cast<T>(0) + static_cast<U>(0))>(0);
		for (int i = 0; i < Size; i++)
		{
			result += vec1.array[i] * vec2.array[i];
			//result += vec1.get(i) * vec2.get(i);
		}
		return result;
	}

	template <int Size, typename T, typename U, typename P1, typename P2>
		requires (Size == 3) && Arithmetic<T> && Arithmetic<U>
	auto cross(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		return Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>(
			vec1.get(1) * vec2.get(2) - vec1.get(2) * vec2.get(1),
			vec1.get(2) * vec2.get(0) - vec1.get(0) * vec2.get(2),
			vec1.get(0) * vec2.get(1) - vec1.get(1) * vec2.get(0)
		);
	}

}

#endif