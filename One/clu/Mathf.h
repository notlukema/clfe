#ifndef CLU_MATHF_H
#define CLU_MATHF_H


namespace clu
{
	class Mathf
	{
	public:


		static float sin(float radians);
		static float cos(float radians);
		static float tan(float radians);
		static float asin(float value);
		static float acos(float value);
		static float atan(float value);
		static float atan2(float x, float y);

		static float sqr(float value);
		static float sqrt(float value);
		static float invSqrt(float value);

		static float abs(float value);
		static float ceil(float value);
		static float floor(float value);

		static float pow(float value, float exponent);
		static float log(float value, float base);
		static float log10(float value);
		static float ln(float value);
		static float exp(float exponent);

	};
}

#endif