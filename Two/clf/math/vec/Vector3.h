#ifndef CLFE_VECTOR_3_H
#define CLFE_VECTOR_3_H

#include "Vector.h"

#include <cstdint>

namespace clfe
{

	template <typename T>
	class Vector3 : public Vector<T, 3>
	{
	public:
		Vector3();
		Vector3(const Vector3<T>& vec3);
		Vector3(T x, T y, T z);

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

	using Vector3b = Vector3<uint8_t>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;

}

// Definitions

namespace clfe
{

	template <typename T>
	Vector3<T>::Vector3() : Vector<T, 3>() {}

	template <typename T>
	Vector3<T>::Vector3(const Vector3<T>& vec3) : Vector<T, 3>(vec3.x(), vec3.y(), vec3.z()) {}

	template <typename T>
	Vector3<T>::Vector3(T x, T y, T z) : Vector<T, 3>(x, y, z) {}

	template <typename T>
	T Vector3<T>::x() const
	{
		return this->array[0];
	}

	template <typename T>
	T Vector3<T>::y() const
	{
		return this->array[1];
	}

	template <typename T>
	T Vector3<T>::z() const
	{
		return this->array[2];
	}

	template <typename T>
	void Vector3<T>::set(T x, T y, T z)
	{
		this->array[0] = x;
		this->array[1] = y;
		this->array[2] = z;
	}

	template <typename T>
	void Vector3<T>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T>
	void Vector3<T>::y(T y)
	{
		this->array[1] = y;
	}

	template <typename T>
	void Vector3<T>::z(T z)
	{
		this->array[2] = z;
	}

}

#endif