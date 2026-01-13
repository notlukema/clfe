#ifndef CLM_VECTOR_3_H
#define CLM_VECTOR_3_H

#include "Vector.h"

namespace clfe
{

	template <typename T>
	class Vector<4, T>
	{
	protected: // Vector reimplementation
		T array[4];

	public:
		Vector() : array{} {}

		Vector(T scalar) : array{ scalar, scalar, scalar, scalar } {}

		template <typename... Args>
			requires (sizeof...(Args) == 4) && AllCompatible<T, Args...>
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : { arr[0], arr[1], arr[2], arr[3] } {}

		Vector(const Vector<4, T>& vec) : array{ vec.array[0], vec.array[1], vec.array[2], vec.array[3] } {}

		inline msize_t size() const
		{
			return 4;
		}

		inline T& operator[](msize_t i)
		{
			return array[i];
		}

		inline const T* get() const
		{
			return static_cast<const T*>(array);
		}

		inline T get(msize_t i) const
		{
			return array[i];
		}

		inline void setAt(msize_t i, T value)
		{
			array[i] = value;
		}

		template <typename U = T>
		U distance() const requires Arithmetic2<T, U>
		{
			return static_cast<U>(sqrt(static_cast<U>(
				array[0] * array[0] +
				array[1] * array[1] +
				array[2] * array[2] +
				array[3] * array[3]
				)));
		}

		template <typename U = T>
		Vector<3, U> normalized() const requires Arithmetic2<T, U>
		{
			T dist = distance<T>();
			return Vector<4, U>(
				static_cast<U>(array[0] / dist),
				static_cast<U>(array[1] / dist),
				static_cast<U>(array[2] / dist),
				static_cast<U>(array[3] / dist)
			);
		}

		Vector<3, T>& normalize() requires Arithmetic<T>
		{
			T dist = distance<T>();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			array[2] = array[2] / dist;
			array[3] = array[3] / dist;
			return *this;
		}

	public: // Vector2 specific
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

	template <typename T>
	using Vector4 = Vector<4, T>;

	using Vector4f = Vector4<float>;
	using Vector4d = Vector4<double>;
	using Vector4i = Vector4<int>;

}


namespace clfe
{

	template <typename T>
	T Vector<4, T>::x() const
	{
		return this->array[0];
	}

	template <typename T>
	T Vector<4, T>::y() const
	{
		return this->array[1];
	}

	template <typename T>
	T Vector<4, T>::z() const
	{
		return this->array[2];
	}

	template <typename T>
	T Vector<4, T>::w() const
	{
		return this->array[3];
	}

	template <typename T>
	void Vector<4, T>::set(T x, T y, T z, T w)
	{
		this->array[0] = x;
		this->array[1] = y;
		this->array[2] = z;
		this->array[3] = w;
	}

	template <typename T>
	void Vector<4, T>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T>
	void Vector<4, T>::y(T y)
	{
		this->array[1] = y;
	}

	template <typename T>
	void Vector<4, T>::z(T z)
	{
		this->array[2] = z;
	}

	template <typename T>
	void Vector<4, T>::w(T w)
	{
		this->array[3] = w;
	}

}

#endif