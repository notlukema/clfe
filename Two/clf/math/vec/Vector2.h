#ifndef CLFE_VECTOR_2_H
#define CLFE_VECTOR_2_H

#include "Vector.h"
#include "../Mathf.h"

namespace clfe
{

	template <typename T>
	class Vector2 : public Vector<T, 2>
	{
	public:
		Vector2();
		Vector2(const Vector2<T>& vec2);
		Vector2(T x, T y);

		T x();
		T y();

		void x(T x);
		void y(T y);

	}

}

#endif