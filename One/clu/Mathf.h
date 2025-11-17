#ifndef CLU_MATHF_H
#define CLU_MATHF_H

#include <cmath>

namespace clu
{
	class Mathf
	{
	public:

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


		
		static inline float sin(float radians) {
			return std::sinf(radians);
		}

		static inline float cos(float radians)
		{
			return std::cosf(radians);
		}

		static inline float tan(float radians)
		{
			return std::tanf(radians);
		}

		static inline float asin(float value)
		{
			return std::asinf(value);
		}

		static inline float acos(float value)
		{
			return std::acosf(value);
		}

		static inline float atan(float value)
		{
			return std::atanf(value);
		}

		static inline float atan2(float y, float x)
		{
			return std::atan2f(y, x);
		}



		static inline float constexpr abs(float value) {
			return value < 0 ? -value : value;
		}

		static inline float ceil(float value) {
			return std::ceilf(value);
		}

		static inline float floor(float value) {
			return std::floor(value);
		}



		static inline float pow(float value, float exponent) {
			return std::powf(value, exponent);
		}

		static inline float log(float value, float base) {
			// Why doesn't cmath have this function?
			return std::logf(value) / std::logf(base);
		}

		static inline float log10(float value) {
			return std::log10f(value);
		}

		static inline float log2(float value) {
			return std::log2f(value);
		}

		static inline float ln(float value) {
			return std::logf(value);
		}

		static inline float exp(float exponent) {
			return std::expf(exponent);
		}



		static inline float constexpr sqr(float value)
		{
			return value * value;
		}

		static inline float sqrt(float value)
		{
			return std::sqrtf(value);
		}

		static inline float invSqrt(float value) {
			return 1.0f / sqrt(value);
		}

		static inline float root(float value, float n) {
			return pow(value, 1.0f / n);
		}

		// Fast

		static inline float constexpr fastSin(float x) {
			// Hit it later
		}

		/*
		Not necessarily as fast anymore
		Many cpus now have hardware implementations that are faster than this software implementation
		*/
		static float fastInvSqrt(float value) {
			long i;
			float x2, y;
			const float threehalfs = 1.5F;
			x2 = value * 0.5F;
			y = value;
			i = *(long*)&y;
			i = 0x5f3759df - (i >> 1);
		}

	};
}

#endif