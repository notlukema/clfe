#ifndef CLFE_VECTOR_OP_H
#define CLFE_VECTOR_OP_H

// Guards against if anyone decides to include this file directly
#include "Vector.h"

namespace clfe
{

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic<T> && Arithmetic<U>
	auto dot(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> decltype(static_cast<T>(0) + static_cast<U>(0))
	{
		auto result = static_cast<decltype(static_cast<T>(0) + static_cast<U>(0))>(0);
		for (msize_t i = 0; i < Size; i++)
		{
			result += vec1.get(i) * vec2.get(i);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires (Size == 3) && Arithmetic<T> && Arithmetic<U>
	auto cross(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		return Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>(
			vec1.get(1) * vec2.get(2) - vec1.get(2) * vec2.get(1),
			vec1.get(2) * vec2.get(0) - vec1.get(0) * vec2.get(2),
			vec1.get(0) * vec2.get(1) - vec1.get(1) * vec2.get(0)
		);
	}

	//
	// Inter-vector operations
	//

	static constexpr int smax(int a, int b)
	{
		return (a > b) ? a : b;
	}

	// Addition

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) + vec2.get(i));
		}
		return result;
	}

	template <msize_t Size1, msize_t Size2, typename T, typename U, typename P1, typename P2>
		requires (Size1 != Size2) && Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size1, T, P1>& vec1, const Vector<Size2, U, P2>& vec2) -> Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		auto result = Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0)), P1>();
		for (msize_t i = 0; i < smax(Size1, Size2); i++)
		{
			result.setAt(i,
				((i < Size1) ? vec1.get(i) : static_cast<T>(0)) +
				((i < Size2) ? vec2.get(i) : static_cast<U>(0))
			);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic3<T, U>
	Vector<Size, T, P1>& operator+=(Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) + vec2.get(i)));
		}
		return vec1;
	}

	// Subtraction

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator-(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) - vec2.get(i));
		}
		return result;
	}

	template <msize_t Size1, msize_t Size2, typename T, typename U, typename P1, typename P2>
		requires (Size1 != Size2) && Arithmetic<T> && Arithmetic<U>
	auto operator-(const Vector<Size1, T, P1>& vec1, const Vector<Size2, U, P2>& vec2) -> Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		auto result = Vector<smax(Size1, Size2), decltype(static_cast<T>(0) + static_cast<U>(0)), P1>();
		for (msize_t i = 0; i < smax(Size1, Size2); i++)
		{
			result.setAt(i,
				((i < Size1) ? vec1.get(i) : static_cast<T>(0)) -
				((i < Size2) ? vec2.get(i) : static_cast<U>(0))
			);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic3<T, U>
	Vector<Size, T, P1>& operator-=(Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) - vec2.get(i)));
		}
		return vec1;
	}

	// Multiplication

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator*(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) * vec2.get(i));
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic3<T, U>
	Vector<Size, T, P1>& operator*=(Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) * vec2.get(i)));
		}
		return vec1;
	}

	// Division

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator/(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P1>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec1.get(i) / vec2.get(i));
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
		requires Arithmetic3<T, U>
	Vector<Size, T, P1>& operator/=(Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec1.setAt(i, static_cast<T>(vec1.get(i) / vec2.get(i)));
		}
		return vec1;
	}

	//
	// Scalar operations
	//

	// Addition

	/* Works with different types, but has code bloat and is quite ambiguous
	
	template <int Size, typename T, typename U, typename P>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size, T, P>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>();
		for (int i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) + scalar);
		}
		return result;
	}
	*/

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Vector<Size, T, P>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) + scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic3<T, U>
	Vector<Size, T, P>& operator+=(Vector<Size, T, P>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) + scalar));
		}
		return vec;
	}

	// Subtraction

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic<T>&& Arithmetic<U>
	auto operator-(const Vector<Size, T, P>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) - scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic3<T, U>
	Vector<Size, T, P>& operator-=(Vector<Size, T, P>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) - scalar));
		}
		return vec;
	}

	// Multiplication

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic<T>&& Arithmetic<U>
	auto operator*(const Vector<Size, T, P>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) * scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic3<T, U>
	Vector<Size, T, P>& operator*=(Vector<Size, T, P>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) * scalar));
		}
		return vec;
	}

	// Division

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic<T>&& Arithmetic<U>
	auto operator/(const Vector<Size, T, P>& vec, U scalar) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>
	{
		auto result = Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0)), P>();
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, vec.get(i) / scalar);
		}
		return result;
	}

	template <msize_t Size, typename T, typename U, typename P>
		requires Arithmetic3<T, U>
	Vector<Size, T, P>& operator/=(Vector<Size, T, P>& vec, U scalar)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			vec.setAt(i, static_cast<T>(vec.get(i) / scalar));
		}
		return vec;
	}

	//
	// Comparisons
	//

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
	bool operator==(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			if (vec1.get(i) != vec2.get(i))
			{
				return false;
			}
		}
		return true;
	}

	template <msize_t Size, typename T, typename U, typename P1, typename P2>
	bool operator!=(const Vector<Size, T, P1>& vec1, const Vector<Size, U, P2>& vec2)
	{
		for (msize_t i = 0; i < Size; i++)
		{
			if (vec1.get(i) != vec2.get(i))
			{
				return true;
			}
		}
		return false;
	}

}

#endif