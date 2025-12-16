#ifndef CLFE_VECTOR_2_H
#define CLFE_VECTOR_2_H

#include "Vector.h"

#include <cstdint>
#include <type_traits>

namespace clfe
{

	template <typename T>
	requires std::is_arithmetic_v<T>
	class Vector2 : public Vector<T, 2>
	{
	public:
		Vector2() : Vector<T, 2>() {}

		Vector2(const Vector2<T>& vec2) : Vector<T, 2>(vec2.x(), vec2.y()) {}

		Vector2(T x, T y) : Vector<T, 2>(x, y) {}

		T x() const
		{
			return this->array[0];
		}

		T y() const
		{
			return this->array[1];
		}

		void set(T x, T y)
		{
			this->array[0] = x;
			this->array[1] = y;
		}

		void x(T x)
		{
			this->array[0] = x;
		}

		void y(T y)
		{
			this->array[1] = y;
		}

	public:/*
		bool operator==(const Vector2<T>& vec2) const;
		bool operator!=(const Vector2<T>& vec2) const;

		Vector2<T> operator+(T value);
		Vector2<T> operator-(T value);
		Vector2<T> operator*(T value);
		Vector2<T> operator/(T value);

		Vector2<T>& operator+=(T value);
		Vector2<T>& operator-=(T value);
		Vector2<T>& operator*=(T value);
		Vector2<T>& operator/=(T value);

		Vector2<T> operator+(const Vector2<T>& vec2);
		Vector2<T> operator-(const Vector2<T>& vec2);
		Vector2<T> operator*(const Vector2<T>& vec2);
		Vector2<T> operator/(const Vector2<T>& vec2);

		Vector2<T>& operator+=(const Vector2<T>& vec2);
		Vector2<T>& operator-=(const Vector2<T>& vec2);
		Vector2<T>& operator*=(const Vector2<T>& vec2);
		Vector2<T>& operator/=(const Vector2<T>& vec2);
		*/

		// Operator overloads
		/*
		template <typename T>
		Vector2<T> Vector2<T>::operator+(T value)
		{
			return Vector2<T>(this->array[0] + value, this->array[1] + value);
		}

		template <typename T>
		Vector2<T> Vector2<T>::operator-(T value)
		{
			return Vector2<T>(this->array[0] - value, this->array[1] - value);
		}

		template <typename T>
		Vector2<T> Vector2<T>::operator*(T value)
		{
			return Vector2<T>(this->array[0] * value, this->array[1] * value);
		}

		template <typename T>
		Vector2<T> Vector2<T>::operator/(T value)
		{
			return Vector2<T>(this->array[0] / value, this->array[1] / value);
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator+=(T value)
		{
			this->array[0] += value;
			this->array[1] += value;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator-=(T value)
		{
			this->array[0] -= value;
			this->array[1] -= value;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator*=(T value)
		{
			this->array[0] *= value;
			this->array[1] *= value;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator/=(T value)
		{
			this->array[0] /= value;
			this->array[1] /= value;
			return *this;
		}

		template <typename T>
		Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec2)
		{
			return Vector2<T>(this->array[0] + vec2.x(), this->array[1] + vec2.y());
		}
		*/
		

	};
}

namespace clfe
{

	using Vector2b = Vector2<uint8_t>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
	using Vector2i = Vector2<int>;

}

#endif