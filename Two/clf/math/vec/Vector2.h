#ifndef CLFE_VECTOR_2_H
#define CLFE_VECTOR_2_H

#include "Vector.h"

#include <cstdint>

namespace clfe
{

	template <typename T>
	class Vector2 : public Vector<T, 2>
	{
	public:
		Vector2();
		Vector2(const Vector2<T>& vec2);
		Vector2(T x, T y);

		T x() const;
		T y() const;

		void set(T x, T y);
		void x(T x);
		void y(T y);

	};

}

namespace clfe
{

	using Vector2b = Vector2<uint8_t>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;

}

// Definitions

namespace clfe
{
	
	template <typename T>
	Vector2<T>::Vector2() : Vector<T, 2>() {}

	template <typename T>
	Vector2<T>::Vector2(const Vector2<T>& vec2) : Vector<T, 2>(vec2.x(), vec2.y()) {}

	template <typename T>
	Vector2<T>::Vector2(T x, T y) : Vector<T, 2>(x, y) {}

	template <typename T>
	T Vector2<T>::x() const
	{
		return this->array[0];
	}

	template <typename T>
	T Vector2<T>::y() const
	{
		return this->array[1];
	}

	template <typename T>
	void Vector2<T>::set(T x, T y)
	{
		this->array[0] = x;
		this->array[1] = y;
	}

	template <typename T>
	void Vector2<T>::x(T x)
	{
		this->array[0] = x;
	}

	template <typename T>
	void Vector2<T>::y(T y)
	{
		this->array[1] = y;
	}

}

#endif