#include "Quaternion.h"

namespace clfe
{

	Quaternion::Quaternion() : x_(0), y_(0), z_(0), w_(1)
	{}

	Quaternion::Quaternion(float x, float y, float z, float w) : x_(x), y_(y), z_(z), w_(w)
	{}

}