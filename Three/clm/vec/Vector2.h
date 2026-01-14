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
		Vector() : array{} {}

		Vector(T scalar) : array{ scalar, scalar } {}

		template <typename... Args>
			requires (sizeof...(Args) == 2) && AllCompatible<T, Args...>
		Vector(Args... args) : array{ static_cast<T>(args)... } {}

		Vector(const T* arr) : array{ arr[0], arr[1] } {}

		Vector(const Vector<2, T>& vec) : array{ vec.array[0], vec.array[1] } {}

		inline msize_t size() const
		{
			return 2;
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

// Implementation
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