#ifndef CLFE_VECTOR_4_H
#define CLFE_VECTOR_4_H

#include "../VecMatCommon.h"
#include "Vector.h"

#include <cstdint>

namespace clfe
{

	template <typename T, typename P>
	class Vector<4, T, P>
	{
	protected: // Reimplementation
		T array[4];

	public:
		template <typename... Args>
			requires (sizeof...(Args) <= 4)
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : array{}
		{
			array[0] = arr[0];
			array[1] = arr[1];
			array[2] = arr[2];
			array[3] = arr[3];
		}

		template <msize_t Size1, typename P1>
			requires (Size1 > 0) && (Size1 <= 4)
		Vector(const Vector<Size1, T, P1>& vec) : array{ vec.array } {}

		template <msize_t Size1, typename P1>
			requires (Size1 > 4)
		Vector(const Vector<Size1, T, P1>& vec) : array{}
		{
			array[0] = vec.get(0);
			array[1] = vec.get(1);
			array[2] = vec.get(2);
			array[3] = vec.get(3);
		}

		inline int size() const
		{
			return 4;
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
				static_cast<P>(array[1] * array[1]) +
				static_cast<P>(array[2] * array[2]) +
				static_cast<P>(array[3] * array[3])
			));
		}

		P distSqr() const requires Arithmetic2<T, P>
		{
			return static_cast<P>(array[0] * array[0]) +
				static_cast<P>(array[1] * array[1]) +
				static_cast<P>(array[2] * array[2]) +
				static_cast<P>(array[3] * array[3]);
		}

		T nativeDist() const requires Arithmetic<T>
		{
			return static_cast<T>(sqrt(
				array[0] * array[0] +
				array[1] * array[1] +
				array[2] * array[2] +
				array[3] * array[3]
			));
		}

		T nativeDistSqr() const requires Arithmetic<T>
		{
			return array[0] * array[0] +
				array[1] * array[1] +
				array[2] * array[2] +
				array[3] * array[3];
		}

		void normalize() requires Arithmetic<T>
		{
			T dist = nativeDist();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			array[2] = array[2] / dist;
			array[3] = array[3] / dist;
		}

		Vector<4, P, P> normalized() const requires Arithmetic<T>
		{
			P dist = distance();
			return Vector<4, P, P>(
				static_cast<P>(array[0]) / dist,
				static_cast<P>(array[1]) / dist,
				static_cast<P>(array[2]) / dist,
				static_cast<P>(array[3]) / dist
			);
		}

	public: // Vector4 specific
		T x() const;
		T y() const;
		T z() const;
		T w() const;

		void set(T x, T y, T z, T w);
		void x(T x);
		void y(T y);
		void z(T z);
		void w(T w);

		inline T r() const
		{
			return x();
		}

		inline T g() const
		{
			return y();
		}

		inline T b() const
		{
			return z();
		}

		inline T a() const
		{
			return w();
		}

		inline void r(T r)
		{
			x(r);
		}

		inline void g(T g)
		{
			y(g);
		}

		inline void b(T b)
		{
			z(b);
		}

		inline void a(T a)
		{
			w(a);
		}

	};

}

namespace clfe
{

	template <typename T, typename P = lowp>
	using Vector4 = Vector<4, T, P>;

	using Vector4b = Vector<4, uint8_t>;
	using Vector4f = Vector<4, float>;
	using Vector4d = Vector<4, double>;
	using Vector4i = Vector<4, int>;

	using Vector4b_lp = Vector<4, uint8_t, lowp>;
	using Vector4f_lp = Vector<4, float, lowp>;
	using Vector4d_lp = Vector<4, double, lowp>;
	using Vector4i_lp = Vector<4, int, lowp>;

	using Vector4b_mp = Vector<4, uint8_t, mediump>;
	using Vector4f_mp = Vector<4, float, mediump>;
	using Vector4d_mp = Vector<4, double, mediump>;
	using Vector4i_mp = Vector<4, int, mediump>;

	using Vector4b_hp = Vector<4, uint8_t, highp>;
	using Vector4f_hp = Vector<4, float, highp>;
	using Vector4d_hp = Vector<4, double, highp>;
	using Vector4i_hp = Vector<4, int, highp>;

}

// Definitions

namespace clfe
{

	template <typename T, typename P>
	T Vector<4, T, P>::x() const
	{
		return this->array[0];
	}

	template <typename T, typename P>
	T Vector<4, T, P>::y() const
	{
		return this->array[1];
	}

	template <typename T, typename P>
	T Vector<4, T, P>::z() const
	{
		return this->array[2];
	}

	template <typename T, typename P>
	T Vector<4, T, P>::w() const
	{
		return this->array[3];
	}

	template <typename T, typename P>
	void Vector<4, T, P>::set(T x, T y, T z, T w)
	{
		this->array[0] = x;
		this->array[1] = y;
		this->array[2] = z;
		this->array[3] = w;
	}

	template <typename T, typename P>
	void Vector<4, T, P>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T, typename P>
	void Vector<4, T, P>::y(T y)
	{
		this->array[1] = y;
	}

	template <typename T, typename P>
	void Vector<4, T, P>::z(T z)
	{
		this->array[2] = z;
	}

	template <typename T, typename P>
	void Vector<4, T, P>::w(T w)
	{
		this->array[3] = w;
	}

}

#endif