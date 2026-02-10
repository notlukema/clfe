#ifndef CLFE_VECMAT_OP_H
#define CLFE_VECMAT_OP_H

// Guards against if anyone decides to include this file directly
#include "vec/Vector.h"
#include "mat/Matrix.h"

namespace clfe
{

	/* NOTE: make vector-matrix multiplication soon
	template <msize_t Cols, msize_t Rows, msize_t Size, typename T, typename U>
		requires (Cols == Size) && Arithmetic<T> && Arithmetic<U>
	auto operator*(const Matrix<Cols, Rows, T>& mat, const Vector<Size, U>& vec) -> Vector<Size, decltype(static_cast<T>(0) + static_cast<U>(0))>
	{
		auto result = Vector<Cols2, Rows1, decltype(static_cast<T>(0) + static_cast<U>(0))>();
		for (msize_t r = 0; r < Rows1; r++)
		{
			for (msize_t c = 0; c < Cols2; c++)
			{
				decltype(static_cast<T>(0) + static_cast<U>(0)) sum = 0;
				for (msize_t k = 0; k < Cols1; k++)
				{
					sum += mat1.get(k, r) * mat2.get(c, k);
				}
				result.setAt(c, r, sum);
			}
		}
		return result;
	}
	*/

}

#endif