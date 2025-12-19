#ifndef CLU_PRINT_H
#define CLU_PRINT_H

#include <cstdio>
#include <type_traits>

// Supplies simple print functions for whichever types are included

namespace clu
{
#ifdef CLFE_VECTOR_H
	template <int Size, typename T, typename P>
		requires (Size > 0)
	void print(const clfe::Vector<Size, T, P>& vec)
	{
		const T* const data = vec.get();
		printf("(");
		for (int i = 0; i < Size; i++)
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
	
}

#endif