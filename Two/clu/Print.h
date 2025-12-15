#ifndef CLU_PRINT_H
#define CLU_PRINT_H

#include <cstdio>

// Supplies simple print functions for whichever types are included

namespace clu
{
#ifdef CLFE_VECTOR_H
	template <typename T, int Size>
	inline void print(const clfe::Vector<T, Size>& vec)
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

#ifdef CLFE_VECTOR_2_H
	template <typename T>
	inline void print(const clfe::Vector2<T>& vec2)
	{
		printf("(%.3f, %.3f)\n", (double)vec2.x(), (double)vec2.y());
	}
#endif

#ifdef CLFE_VECTOR_3_H
	template <typename T>
	inline void print(const clfe::Vector3<T>& vec3)
	{
		printf("(%.3f, %.3f, %.3f)\n", (double)vec3.x(), (double)vec3.y(), (double)vec3.z());
	}
#endif

#ifdef CLFE_VECTOR_4_H
	template <typename T>
	inline void print(const clfe::Vector4<T>& vec4)
	{
		printf("(%.3f, %.3f, %.3f, %.3f)\n", vec4.x(), vec4.y(), vec4.z(), vec4.w());
	}
#endif
	
}

#endif