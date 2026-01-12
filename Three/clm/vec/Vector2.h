#ifndef CLM_VECTOR_2_H
#define CLM_VECTOR_2_H

#include "Vector.h"

namespace clfe
{

	template <typename T>
	class Vector<2, T>
	{
	protected: // Vector reimplementation
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

		template <msize_t Size1>
			requires (Size1 <= 2)
		Vector(const Vector<Size1, T>& vec) : array{ vec.array } {}

		template <msize_t Size1>
			requires (Size1 > 2)
		Vector(const Vector<Size1, T>& vec) : array{}
		{
			array[0] = vec.get(0);
			array[1] = vec.get(1);
		}

		inline int size() const
		{
			return 2;
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
				array[1] * array[1]
			)));
		}

		template <typename U = T>
		Vector<2, U> normalized() const requires Arithmetic2<T, U>
		{
			T dist = distance<T>();
			return Vector<2, U>(
				static_cast<U>(array[0] / dist),
				static_cast<U>(array[1] / dist)
			);
		}

		Vector<2, T>& normalize() requires Arithmetic<T>
		{
			T dist = distance<T>();
			array[0] = array[0] / dist;
			array[1] = array[1] / dist;
			return *this;
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

	template <typename T>
	using Vector2 = Vector<2, T>;

	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;

}


namespace clfe
{

	template <typename T>
	T Vector<2, T>::x() const
	{
		return this->array[0];
	}

	template <typename T>
	T Vector<2, T>::y() const
	{
		return this->array[1];
	}

	template <typename T>
	void Vector<2, T>::set(T x, T y)
	{
		this->array[0] = x;
		this->array[1] = y;
	}

	template <typename T>
	void Vector<2, T>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T>
	void Vector<2, T>::y(T y)
	{
		this->array[1] = y;
	}

}

#endif