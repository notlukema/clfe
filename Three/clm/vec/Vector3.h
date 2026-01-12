#ifndef CLM_VECTOR_3_H
#define CLM_VECTOR_3_H

#include "Vector.h"

namespace clfe
{

	template <typename T>
	class Vector<3, T>
	{
	protected: // Vector reimplementation
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

		template <msize_t Size1>
			requires (Size1 <= 3)
		Vector(const Vector<Size1, T>& vec) : array{ vec.array } {}

		template <msize_t Size1>
			requires (Size1 > 3)
		Vector(const Vector<Size1, T>& vec) : array{}
		{
			array[0] = vec.get(0);
			array[1] = vec.get(1);
			array[2] = vec.get(2);
		}

		inline int size() const
		{
			return 3;
		}

		T& operator[](int i)
		{
			return array[i];
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

		template <typename U = T>
		U distance() const requires Arithmetic2<T, U>
		{
			return static_cast<U>(sqrt(static_cast<U>(
				array[0] * array[0] +
				array[1] * array[1] +
				array[2] * array[2]
				)));
		}

		template <typename U = T>
		Vector<3, U> normalized() const requires Arithmetic2<T, U>
		{
			T dist = distance<T>();
			return Vector<3, U>(
				static_cast<U>(array[0] / dist),
				static_cast<U>(array[1] / dist),
				static_cast<U>(array[2] / dist)
			);
		}

		Vector<3, T>& normalize() requires Arithmetic<T>
		{
			T dist = distance<T>();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			array[2] = array[2] / dist;
			return *this;
		}

	public: // Vector2 specific
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

	template <typename T>
	using Vector3 = Vector<3, T>;

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3i = Vector3<int>;

}


namespace clfe
{

	template <typename T>
	T Vector<3, T>::x() const
	{
		return this->array[0];
	}

	template <typename T>
	T Vector<3, T>::y() const
	{
		return this->array[1];
	}

	template <typename T>
	T Vector<3, T>::z() const
	{
		return this->array[2];
	}

	template <typename T>
	void Vector<3, T>::set(T x, T y, T z)
	{
		this->array[0] = x;
		this->array[1] = y;
		this->array[2] = z;
	}

	template <typename T>
	void Vector<3, T>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T>
	void Vector<3, T>::y(T y)
	{
		this->array[1] = y;
	}

	template <typename T>
	void Vector<3, T>::z(T z)
	{
		this->array[2] = z;
	}

}

#endif