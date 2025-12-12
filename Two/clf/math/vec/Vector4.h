#ifndef CLFE_VECTOR_4_H
#define CLFE_VECTOR_4_H

#include "Vector.h"

namespace clfe
{

	template <typename T>
	class Vector4 : public Vector<T, 4>
	{
	public:
		Vector4();
		Vector4(const Vector4<T>& vec4);
		Vector4(T x, T y, T z, T w);

		T x();
		T y();
		T z();
		T w();

		void x(T x);
		void y(T y);
		void z(T z);
		void w(T w);

		inline T r()
		{
			return x();
		}

		inline T g()
		{
			return y();
		}

		inline T b()
		{
			return z();
		}

		inline T a()
		{
			return w();
		}

		inline void r(T r)
		{
			x(r);
		}

		inline void g(T g)
		{
			y(g);
		}

		inline void b(T b)
		{
			z(b);
		}

		inline void a(T a)
		{
			w(a);
		}

	};

}

// Definitions

namespace clfe
{

	template <typename T>
	Vector4<T>::Vector4(T x, T y, T z, T w)
	{

	}

}

#endif