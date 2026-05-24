#ifndef CLM_QUATERNION_H
#define CLM_QUATERNION_H

namespace clfe
{

	class Quaternion
	{
	private:
		float x_, y_, z_, w_;

	public:
		Quaternion();
		Quaternion(float x, float y, float z, float w);

		inline float x()
		{
			return x_;
		}

		inline float y()
		{
			return y_;
		}

		inline float z()
		{
			return z_;
		}

		inline float w()
		{
			return w_;
		}

	};

}

#endif