#ifndef CLM_MATRIX_OP_H
#define CLM_MATRIX_OP_H

// Guards against if anyone decides to include this file directly
#include "Matrix.h"

namespace clfe
{

	static constexpr int smax2(int a, int b)
	{
		return (a > b) ? a : b;
	}

	// Addition

	template <msize_t Rows, msize_t Cols, typename T, typename U>
		requires Arithmetic<T>&& Arithmetic<U>
	auto operator+(const Matrix<Rows, Cols, T>& mat1, const Matrix<Rows, Cols, U>& mat2) -> Matrix<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<Rows, Cols, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows; r++)
		{
			result.setRow(r, mat1.get(r) + mat2.get(r));
		}
		return result;
	}

	template <msize_t Rows1, msize_t Cols1, msize_t Rows2, msize_t Cols2, typename T, typename U>
		requires Arithmetic<T> && Arithmetic<U>
	auto operator+(const Matrix<Rows1, Cols1, T>& mat1, const Matrix<Rows2, Cols2, U>& mat2) -> Matrix<smax2(Rows1, Rows2), smax2(Cols1, Cols2), decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Matrix<smax2(Rows1, Rows2), smax2(Cols1, Cols2), decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < smax2(Rows1, Rows2); r++)
		{
			result.setRow(r,
				((r < Rows1) ? mat1.getRow(r) : Vector<Cols1, T>()) +
				((r < Rows2) ? mat2.getRow(r) : Vector<Cols2, U>())
			);
		}
		return result;
	}

}

#endif