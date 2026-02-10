#ifndef CLU_PRINT_H
#define CLU_PRINT_H

#include <cstdio>
#include <type_traits>

// Supplies simple print functions for whichever types are included

namespace clfe
{

	template <typename T>
	static inline void printNum(const T& value) requires std::is_floating_point_v<T>
	{
		printf("%.3f", (double)value);
	}

	template <typename T>
	static inline void printNum(const T& value) requires std::is_integral_v<T>
	{
		printf("%.0f", (double)value);
	}

#ifdef CLM_VECTOR_H
	template <msize_t Size, typename T>
	void print(const Vector<Size, T>& vec)
	{
		printf("(");
		for (msize_t i = 0; i < Size; i++)
		{
			printNum<T>(vec.get(i));
			if (i < Size - 1)
			{
				printf(", ");
			}
		}
		printf(")\n");
	}
#endif
	
#ifdef CLM_MATRIX_H
	template <msize_t Cols, msize_t Rows, typename T>
	void print(const Matrix<Cols, Rows, T>& mat)
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
				printNum<T>(mat.get(c, r));
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