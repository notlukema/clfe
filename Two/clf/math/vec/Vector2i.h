#ifndef CLFE_VECTOR2I_H
#define CLFE_VECTOR2I_H

#include "Vector.h"

namespace clfe
{

	class Vector2i : public Vector<int, 2>
	{
	public:
		Vector2i();
		Vector2i(int x, int y);
		Vector2i(int* data);

		void set(int x, int y);
		void x(int x);
		void y(int y);

		int x();
		int y();

	};

}

#endif