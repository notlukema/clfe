#ifndef CLFE_VECTOR_4_H
#define CLFE_VECTOR_4_H

#include "Vector.h"

#include <cstdint>

namespace clfe
{

	template <typename T>
	class Vector4 : public Vector<T, 4>
	{
	public:
		Vector4();
		Vector4(const Vector4<T>& vec4);
		Vector4(T x, T y, T z, T w);

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

	using Vector4b = Vector4<uint8_t>;
	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int>;

}

// Definitions

namespace clfe
{

	template <typename T>
	Vector4<T>::Vector4() : Vector<T, 4>() {}

	template <typename T>
	Vector4<T>::Vector4(const Vector4<T>& vec4) : Vector<T, 4>(vec4.x(), vec4.y(), vec4.z(), vec4.w()) {}

	template <typename T>
	Vector4<T>::Vector4(T x, T y, T z, T w) : Vector<T, 4>(x, y, z, w) {}

	template <typename T>
	T Vector4<T>::x() const
	{
		return this->array[0];
	}

	template <typename T>
	T Vector4<T>::y() const
	{
		return this->array[1];
	}

	template <typename T>
	T Vector4<T>::z() const
	{
		return this->array[2];
	}

	template <typename T>
	T Vector4<T>::w() const
	{
		return this->array[3];
	}

	template <typename T>
	void Vector4<T>::set(T x, T y, T z, T w)
	{
		this->array[0] = x;
		this->array[1] = y;
		this->array[2] = z;
		this->array[3] = w;
	}

	template <typename T>
	void Vector4<T>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T>
	void Vector4<T>::y(T y)
	{
		this->array[1] = y;
	}

	template <typename T>
	void Vector4<T>::z(T z)
	{
		this->array[2] = z;
	}

	template <typename T>
	void Vector4<T>::w(T w)
	{
		this->array[3] = w;
	}

}

#endif