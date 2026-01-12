#ifndef CLU_PRINT_H
#define CLU_PRINT_H

#include <cstdio>
#include <type_traits>

// Supplies simple print functions for whichever types are included

namespace clfe
{

#ifdef CLM_VECTOR_H
	template <msize_t Size, typename T>
	void print(const Vector<Size, T>& vec)
	{
		printf("(");
		for (msize_t i = 0; i < Size; i++)
		{
			printf("%.3f", (double)vec.get(i));
			if (i < Size - 1)
			{
				printf(", ");
			}
		}
		printf(")\n");
	}
#endif
	
#ifdef CLM_MATRIX_H
	template <msize_t Rows, msize_t Cols, typename T>
	void print(const Matrix<Rows, Cols, T>& mat)
	{
		printf("[ ");
		for (msize_t r = 0; r < Rows; r++)
		{
			if (r > 0)
			{
				printf("  ");
			}
			Vector<Cols, T> row = mat.getRow(r);
			for (msize_t c = 0; c < Cols; c++)
			{
				printf("%.3f", (double)row.get(c));
				if (r < Rows - 1 || c < Cols - 1)
				{
					printf(", ");
				}
			}
			if (r < Rows - 1)
			{
				printf("\n");
			}
		}
		printf("  ]\n");
	}
#endif
	
}

#endif