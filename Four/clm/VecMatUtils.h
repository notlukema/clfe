#ifndef CLFE_VECMAT_UTILS_H
#define CLFE_VECMAT_UTILS_H

// Guards against if anyone decides to include this file directly
#include "vec/Vector.h"
#include "mat/Matrix.h"

namespace clfe
{

	template <msize_t Size, typename T>
	inline Matrix<Size, 1, T> toMatrix(const Vector<Size, T>& vec)
	{
		Matrix<Size, 1, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(0, i, vec.get(i));
		}
		return result;
	}

	template <msize_t Size, typename T>
	Vector<Size, T> toVector(const Matrix<Size, 1, T>& mat)
	{
		Vector<Size, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, mat.get(i, 0));
		}
		return result;
	}

	template <msize_t Size, typename T>
	Vector<Size, T> toVector(const Matrix<1, Size, T>& mat)
	{
		Vector<Size, T> result;
		for (msize_t i = 0; i < Size; i++)
		{
			result.setAt(i, mat.get(0, i));
		}
		return result;
	}


}

#endif