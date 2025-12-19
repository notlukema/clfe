#ifndef CLFE_VECTOR_2_H
#define CLFE_VECTOR_2_H

#include "Vector.h"

#include <cstdint>
#include <type_traits>

namespace clfe
{

	template <typename T, typename P>
	class Vector<2, T, P>
	{
	protected: // Reimplementation
		T array[2];

	public:
		template <typename... Args>
			requires (sizeof...(Args) <= 2)
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		template <typename P1>
		Vector(const Vector<2, T, P1>& vec) : array{}
		{
			array[0] = vec.array[0];
			array[1] = vec.array[1];
		}

		int size() const
		{
			return 2;
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
			return static_cast<P>(sqrt(
				static_cast<P>(array[0] * array[0]) +
				static_cast<P>(array[1] * array[1])
			));
		}

		P distSqr() const requires Arithmetic2<T, P>
		{
			return static_cast<P>(array[0] * array[0]) +
				static_cast<P>(array[1] * array[1]);
		}

		T nativeDist() const requires Arithmetic<T>
		{
			return static_cast<T>(sqrt(
				array[0] * array[0] +
				array[1] * array[1]
			));
		}

		T nativeDistSqr() const requires Arithmetic<T>
		{
			return array[0] * array[0] +
				array[1] * array[1];
		}

		void normalize() requires Arithmetic<T>
		{
			T dist = nativeDist();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
		}

		template <int Size0, typename T0, typename U0, typename P1, typename P2>
			requires (Size0 > 0) && Arithmetic<T0>&& Arithmetic<U0>
		friend auto dot(const Vector<Size0, T0, P1>& vec1, const Vector<Size0, U0, P2>& vec2) -> decltype(static_cast<T0>(0) + static_cast<U0>(0));

	public: // Vector2 specific
		T x() const;
		T y() const;

		void set(T x, T y);
		void x(T x);
		void y(T y);

		inline T u() const
		{
			return x();
		}

		inline T v() const
		{
			return y();
		}

		void u(T u)
		{
			x(u);
		}

		void v(T v)
		{
			y(v);
		}

	};

}

namespace clfe
{

	using Vector2b = Vector<2, uint8_t>;
	using Vector2f = Vector<2, float>;
	using Vector2d = Vector<2, double>;
	using Vector2i = Vector<2, int>;

}

// Definitions

namespace clfe
{

	template <typename T, typename P>
	T Vector<2, T, P>::x() const
	{
		return this->array[0];
	}

	template <typename T, typename P>
	T Vector<2, T, P>::y() const
	{
		return this->array[1];
	}

	template <typename T, typename P>
	void Vector<2, T, P>::set(T x, T y)
	{
		this->array[0] = x;
		this->array[1] = y;
	}

	template <typename T, typename P>
	void Vector<2, T, P>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T, typename P>
	void Vector<2, T, P>::y(T y)
	{
		this->array[1] = y;
	}

}

#endif