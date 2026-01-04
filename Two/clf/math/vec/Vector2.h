#ifndef CLFE_VECTOR_2_H
#define CLFE_VECTOR_2_H

#include "../VecMatCommon.h"
#include "Vector.h"

#include <cstdint>

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

		Vector(const T* arr) : array{}
		{
			array[0] = arr[0];
			array[1] = arr[1];
		}

		template <msize_t Size1, typename P1>
			requires (Size1 > 0) && (Size1 <= 2)
		Vector(const Vector<Size1, T, P1>& vec) : array{ vec.array } {}

		template <msize_t Size1, typename P1>
			requires (Size1 > 2)
		Vector(const Vector<Size1, T, P1>& vec) : array{}
		{
			array[0] = vec.get(0);
			array[1] = vec.get(1);
		}

		/*
		template <typename P1>
		Vector(const Vector<2, T, P1>& vec) : array{}
		{
			array[0] = vec.array[0];
			array[1] = vec.array[1];
		}

		template <int Size1, typename P1>
			requires (Size1 > 0) && (Size1 != 2)
		Vector(const Vector<Size1, T, P1>& vec) : array{}
		{
			int minSize = (2 < Size1) ? 2 : Size1;
			for (int i = 0; i < minSize; i++)
			{
				array[i] = vec.get(i);
			}
			for (int i = minSize; i < 2; i++)
			{
				array[i] = static_cast<T>(0);
			}
		}
		*/

		inline int size() const
		{
			return 2;
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

		Vector<2, P, P> normalized() const requires Arithmetic<T>
		{
			P dist = distance();
			return Vector<2, P, P>(
				static_cast<P>(array[0]) / dist,
				static_cast<P>(array[1]) / dist
			);
		}

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

	template <typename T, typename P = lowp>
	using Vector2 = Vector<2, T, P>;

	using Vector2b = Vector<2, uint8_t>;
	using Vector2f = Vector<2, float>;
	using Vector2d = Vector<2, double>;
	using Vector2i = Vector<2, int>;

	using Vector2b_lp = Vector<2, uint8_t, lowp>;
	using Vector2f_lp = Vector<2, float, lowp>;
	using Vector2d_lp = Vector<2, double, lowp>;
	using Vector2i_lp = Vector<2, int, lowp>;

	using Vector2b_mp = Vector<2, uint8_t, mediump>;
	using Vector2f_mp = Vector<2, float, mediump>;
	using Vector2d_mp = Vector<2, double, mediump>;
	using Vector2i_mp = Vector<2, int, mediump>;

	using Vector2b_hp = Vector<2, uint8_t, highp>;
	using Vector2f_hp = Vector<2, float, highp>;
	using Vector2d_hp = Vector<2, double, highp>;
	using Vector2i_hp = Vector<2, int, highp>;

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