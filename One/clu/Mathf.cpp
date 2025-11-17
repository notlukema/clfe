#include "Mathf.h"

#include<cmath>

using namespace clu;

float Mathf::sin(float radians)
{
	return std::sinf(radians);
}

static float cos(float radians)
{
	return std::cosf(radians);
}

static float tan(float radians)
{
	return std::tanf(radians);
}

static float asin(float value)
{
	return std::asinf(value);
}

static float acos(float value)
{
	return std::acosf(value);
}

static float sqrt(float value)
{
	return std::sqrtf(value);
}