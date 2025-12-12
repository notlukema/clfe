#include "Vector2i.h"

#include "Vector.h"

namespace clfe
{

	Vector2i::Vector2i()
	{
		arr = new int[2] {0, 0};
	}

	Vector2i::Vector2i(int x, int y)
	{
		arr = new int[2] {x, y};
	}

	Vector2i::Vector2i(int* data) : Vector(data) {};

	void Vector2i::set(int x, int y)
	{
		arr[0] = x;
		arr[1] = y;
	}

	void Vector2i::x(int x)
	{
		arr[0] = x;
	}

	void Vector2i::y(int y)
	{
		arr[1] = y;
	}

	int Vector2i::x()
	{
		return arr[0];
	}

	int Vector2i::y()
	{
		return arr[1];
	}

}