#ifndef CLFE_MATHF_H
#define CLFE_MATHF_H

#include <cmath>

namespace clu
{

	static constexpr float PI = 3.1415927f;
	static constexpr float E = 2.7182818f;
	// Epsilon

	static constexpr int factorial(int num) {
		if (num > 1) {
			return num * factorial(num - 1);
		}
		return 1;
	}

	static constexpr float invFactorial(int num) {
		return 1.0f / static_cast<float>(factorial(num));
	}



	static inline float sinf(float radians) {
		return std::sinf(radians);
	}

	static inline float cosf(float radians)
	{
		return std::cosf(radians);
	}
	
	static inline float tanf(float radians)
	{
		return std::tanf(radians);
	}

	static inline float asinf(float value)
	{
		return std::asinf(value);
	}

	static inline float acosf(float value)
	{
		return std::acosf(value);
	}

	static inline float atanf(float value)
	{
		return std::atanf(value);
	}

	static inline float atan2f(float y, float x)
	{
		return std::atan2f(y, x);
	}



	static inline float constexpr absf(float value) {
		return value < 0 ? -value : value;
	}

	static inline float ceilf(float value) {
		return std::ceilf(value);
	}

	static inline float floorf(float value) {
		return std::floor(value);
	}



	static inline float powf(float value, float exponent) {
		return std::powf(value, exponent);
	}

	static inline float logf(float value, float base) {
		// Why doesn't cmath have this function?
		return std::logf(value) / std::logf(base);
	}

	static inline float log10f(float value) {
		return std::log10f(value);
	}

	static inline float log2f(float value) {
		return std::log2f(value);
	}

	static inline float lnf(float value) {
		return std::logf(value);
	}

	static inline float expf(float exponent) {
		return std::expf(exponent);
	}



	static inline float constexpr sqrf(float value)
	{
		return value * value;
	}

	static inline float sqrtf(float value)
	{
		return std::sqrtf(value);
	}

	static inline float invSqrtf(float value) {
		return 1.0f / std::sqrtf(value);
	}

	static inline float rootf(float value, float n) {
		return std::powf(value, 1.0f / n);
	}

	// Fast

	static inline float constexpr fastSinf(float x) {
		return x;
	}

	/*
	Not necessarily as fast anymore
	Many cpus now have hardware implementations that are faster than this software implementation
	*/
	static float fastInvSqrtf(float value) {
		long i;
		float x2, y;
		const float threehalfs = 1.5F;
		x2 = value * 0.5F;
		y = value;
		i = *(long*)&y;
		i = 0x5f3759df - (i >> 1);
	}

}

#endif