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

}

#endif