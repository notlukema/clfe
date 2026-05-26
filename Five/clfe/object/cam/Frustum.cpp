#include "Frustum.h"

#include "clm/Mathf.h"

namespace clfe
{

	Frustum::Frustum(float near, float far) : near_(near), far_(far)
	{}

	FrustumFOV::FrustumFOV(float fov, float near, float far, float aspectRatio) : Frustum(near, far), fov_(fov), aspect(aspectRatio)
	{}

	Matrix<4, 4, float> FrustumFOV::projectionMat()
	{
		return Matrix<4, 4, float>(
			1.0f / (aspect * tan(fov_ * 0.5f)), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tan(fov_ * 0.5f), 0.0f, 0.0f,
			0.0f, 0.0f, -(far_ + near_) / (far_ - near_), -(2.0f * far_ * near_) / (far_ - near_),
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

	Matrix<4, 4, float> FrustumFOV::projectionMat(float width, float height)
	{
		return Matrix<4, 4, float>(
			1.0f / (width / height * tan(fov_ * 0.5f)), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tan(fov_ * 0.5f), 0.0f, 0.0f,
			0.0f, 0.0f, -(far_ + near_) / (far_ - near_), -(2.0f * far_ * near_) / (far_ - near_),
			0.0f, 0.0f, -1.0f, 0.0f
		);
	}

}