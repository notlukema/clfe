#ifndef CLU_PRINT_H
#define CLU_PRINT_H

#include "TypeTraits.h"

#include <cstdio>


// Supplies simple print functions for whichever types are included
// Add as needed

namespace clfe
{

	template <typename T>
	static inline void printNum(const T& value) requires IsFloatingPoint<T>
	{
		printf("%.3f", (double)value);
	}

	template <typename T>
	static inline void printNum(const T& value) requires IsIntegral<T>
	{
		printf("%d", value);
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

#ifdef CLFE_SYSTEM_H
	template <typename T>
	void print(InstanceListHandle<T>* list)
	{
		printf("Instance List <");
		printf(list->getTypeName());
		printf("> (%d) [", list->length());
		bool first = true;
		for (T* obj : *list)
		{
			if (first)
			{
				first = false;
				printf("%p", obj);
			}
			else
			{
				printf(", %p", obj);
			}
		}
		printf("]\n");
	}

	template <typename T>
	void print(InstanceListHandle<T> list)
	{
		print(&list);
	}

	template <typename T>
	void print(InstanceList<T>* list)
	{
		print(list->getHandle());
	}
#endif

#ifdef CLFE_PIPELINEDATA_H
	void print(const PipelineData& data)
	{
		printf("Pipeline Data for %s [\n", data.PipelineName.get_char());
		printf("   Vendor: %s\n", data.VendorName.get_char());
		printf("   Renderer: %s\n", data.RendererName.get_char());
		printf("   Version: %s\n", data.VersionString.get_char());
		printf("   Version Major: %d\n", data.VersionMajor);
		printf("   Version Minor: %d\n", data.VersionMinor);
		printf("]\n");
	}
#endif
	
}

#endif