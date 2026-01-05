#ifndef CLU_PRINT_H
#define CLU_PRINT_H

#include <cstdio>
#include <type_traits>

// Supplies simple print functions for whichever types are included

namespace clu
{

#ifdef CLFE_VECTOR_H
	template <clfe::msize_t Size, typename T, typename P>
	void print(const clfe::Vector<Size, T, P>& vec)
	{
		const T* const data = vec.get();
		printf("(");
		for (clfe::msize_t i = 0; i < Size; i++)
		{
			printf("%.3f", (double)data[i]);
			if (i < Size - 1)
			{
				printf(", ");
			}
		}
		printf(")\n");
	}
#endif
	
#ifdef CLFE_MATRIX_H
	template <clfe::msize_t Rows, clfe::msize_t Cols, typename T, typename P>
	void print(const clfe::Matrix<Rows, Cols, T, P>& mat)
	{
		const clfe::Vector<Cols, T, P>* const data = mat.get();
		printf("[ ");
		for (clfe::msize_t r = 0; r < Rows; r++)
		{
			if (r > 0)
			{
				printf("  ");
			}
			for (clfe::msize_t c = 0; c < Cols; c++)
			{
				printf("%.3f", (double)data[r].get(c));
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