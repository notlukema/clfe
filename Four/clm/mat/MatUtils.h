#ifndef CLM_MATRIX_UTILS_H
#define CLM_MATRIX_UTILS_H

// Guards against if anyone decides to include this file directly
#include "Matrix.h"

namespace clfe // Utility functions
{

	template <msize_t Cols, msize_t Rows, msize_t Cols0, msize_t Rows0, typename T> // Could try replacing Cols and Cols0 with one template parameter, same with Rows and Rows0
	inline Matrix<Cols, Rows, T> resize(const Matrix<Cols0, Rows0, T>& mat) requires (Cols == Cols0) && (Rows == Rows0)
	{
		return Matrix<Cols, Rows, T>(mat);
	}

	template <msize_t Cols, msize_t Rows, msize_t Cols0, msize_t Rows0, typename T>
	Matrix<Cols, Rows, T> resize(const Matrix<Cols0, Rows0, T>& mat) requires (Cols != Cols0) || (Rows != Rows0)
	{
		Matrix<Cols, Rows, T> result;
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, (r < Rows0) ? resize<Cols>(mat.getRow(r)) : Vector<Cols, T>());
		}
		return result;
	}

	template <typename T, msize_t Cols, msize_t Rows, typename U>
		requires Compatible<T, U>
	inline Matrix<Cols, Rows, T> cast(const Matrix<Cols, Rows, U>& mat)
	{
		return Matrix<Cols, Rows, T>(mat);
	}

	// Transformation matrices functions

	template <typename T = float>
	Matrix<4, 4, T> scale(T scale)
	{
		return Matrix<4, 4, T>(
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, scale, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> scale(T scaleX, T scaleY, T scaleZ)
	{
		return Matrix<4, 4, T>(
			scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> translate(T tx, T ty, T tz)
	{
		return Matrix<4, 4, T>(
			1, 0, 0, tx,
			0, 1, 0, ty,
			0, 0, 1, tz,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> rotateX(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> rotateY(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1
		);
	}

	template <typename T = float>
	Matrix<4, 4, T> rotateZ(float rad)
	{
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		return Matrix<4, 4, T>(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	// Weird
	template <typename T = float>
		requires Arithmetic<T>
	Matrix<4, 4, T> rotate(float rad, Vector<3, T> axis)
	{
		axis = axis.normalized();
		T c = static_cast<T>(cos(rad));
		T s = static_cast<T>(sin(rad));
		T t = static_cast<T>(1) - c;
		T x = axis.get(0);
		T y = axis.get(1);
		T z = axis.get(2);
		return Matrix<4, 4, T>(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0,
			0, 0, 0, 1
		);
	}

}

#endif