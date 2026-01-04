#ifndef CLFE_VECTOR_3_H
#define CLFE_VECTOR_3_H

#include "../VecMatCommon.h"
#include "Vector.h"

#include <cstdint>

namespace clfe
{

	template <typename T, typename P>
	class Vector<3, T, P>
	{
	protected: // Reimplementation
		T array[3];

	public:
		template <typename... Args>
			requires (sizeof...(Args) <= 3)
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : array{}
		{
			array[0] = arr[0];
			array[1] = arr[1];
			array[2] = arr[2];
		}

		template <msize_t Size1, typename P1>
			requires (Size1 > 0) && (Size1 <= 3)
		Vector(const Vector<Size1, T, P1>& vec) : array{ vec.array } {}

		template <msize_t Size1, typename P1>
			requires (Size1 > 3)
		Vector(const Vector<Size1, T, P1>& vec) : array{}
		{
			array[0] = vec.get(0);
			array[1] = vec.get(1);
			array[2] = vec.get(2);
		}

		inline int size() const
		{
			return 3;
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
				static_cast<P>(array[2] * array[2])
			));
		}

		P distSqr() const requires Arithmetic2<T, P>
		{
			return static_cast<P>(array[0] * array[0]) +
				static_cast<P>(array[1] * array[1]) +
				static_cast<P>(array[2] * array[2]);
		}

		T nativeDist() const requires Arithmetic<T>
		{
			return static_cast<T>(sqrt(
				array[0] * array[0] +
				array[1] * array[1] +
				array[2] * array[2]
			));
		}

		T nativeDistSqr() const requires Arithmetic<T>
		{
			return array[0] * array[0] +
				array[1] * array[1] +
				array[2] * array[2];
		}

		void normalize() requires Arithmetic<T>
		{
			T dist = nativeDist();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			array[2] = array[2] / dist;
		}

		Vector<3, P, P> normalized() const requires Arithmetic<T>
		{
			P dist = distance();
			return Vector<3, P, P>(
				static_cast<P>(array[0]) / dist,
				static_cast<P>(array[1]) / dist,
				static_cast<P>(array[2]) / dist
			);
		}

	public: // Vector3 specific
		T x() const;
		T y() const;
		T z() const;

		void set(T x, T y, T z);
		void x(T x);
		void y(T y);
		void z(T z);

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

	};

}

namespace clfe
{

	template <typename T, typename P = lowp>
	using Vector3 = Vector<3, T, P>;

	using Vector3b = Vector<3, uint8_t>;
	using Vector3f = Vector<3, float>;
	using Vector3d = Vector<3, double>;
	using Vector3i = Vector<3, int>;

	using Vector3b_lp = Vector<3, uint8_t, lowp>;
	using Vector3f_lp = Vector<3, float, lowp>;
	using Vector3d_lp = Vector<3, double, lowp>;
	using Vector3i_lp = Vector<3, int, lowp>;

	using Vector3b_mp = Vector<3, uint8_t, mediump>;
	using Vector3f_mp = Vector<3, float, mediump>;
	using Vector3d_mp = Vector<3, double, mediump>;
	using Vector3i_mp = Vector<3, int, mediump>;

	using Vector3b_hp = Vector<3, uint8_t, highp>;
	using Vector3f_hp = Vector<3, float, highp>;
	using Vector3d_hp = Vector<3, double, highp>;
	using Vector3i_hp = Vector<3, int, highp>;

}

// Definitions

namespace clfe
{

	template <typename T, typename P>
	T Vector<3, T, P>::x() const
	{
		return this->array[0];
	}

	template <typename T, typename P>
	T Vector<3, T, P>::y() const
	{
		return this->array[1];
	}

	template <typename T, typename P>
	T Vector<3, T, P>::z() const
	{
		return this->array[2];
	}

	template <typename T, typename P>
	void Vector<3, T, P>::set(T x, T y, T z)
	{
		this->array[0] = x;
		this->array[1] = y;
		this->array[2] = z;
	}

	template <typename T, typename P>
	void Vector<3, T, P>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T, typename P>
	void Vector<3, T, P>::y(T y)
	{
		this->array[1] = y;
	}

	template <typename T, typename P>
	void Vector<3, T, P>::z(T z)
	{
		this->array[2] = z;
	}

}

#endif