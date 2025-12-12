#ifndef CLFE_VECTOR_3_H
#define CLFE_VECTOR_3_H

#include "Vector.h"

namespace clfe
{

	template <typename T>
	class Vector3 : public Vector<T, 3>
	{
	public:
		Vector3(T x, T y, T z);

	};

}

#endif