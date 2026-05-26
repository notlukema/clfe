#ifndef CLFE_FRUSTUM_H
#define CLFE_FRUSTUM_H

#include "clm/MatrixImpl.h"

#include "TypeTraits.h"

namespace clfe
{

	class Frustum
	{
	protected:
		float near_, far_;

		Frustum(float near, float far);

	public:
		virtual Matrix<4, 4, float> projectionMat() = 0;
		virtual Matrix<4, 4, float> projectionMat(float width, float height) = 0;

		inline float near() const
		{
			return near_;
		}

		inline void setNear(float near)
		{
			near_ = near;
		}

		inline float far() const
		{
			return far_;
		}

		inline void setFar(float far)
		{
			far_ = far;
		}

	};

	class FrustumFOV : public Frustum
	{
	protected:
		float fov_, aspect;

	public:
		FrustumFOV(float fov, float near, float far, float aspectRatio = 1.0f);

		virtual Matrix<4, 4, float> projectionMat() override;
		virtual Matrix<4, 4, float> projectionMat(float width, float height) override;

		inline float fov() const
		{
			return fov_;
		}

		inline void setFov(float fov)
		{
			fov_ = fov;
		}

		inline float aspectRatio() const
		{
			return aspect;
		}

		inline void setAspectRatio(float aspectRatio)
		{
			aspect = aspectRatio;
		}

	};

	//class Frustum

}

#endif