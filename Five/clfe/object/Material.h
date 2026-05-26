#include "Material_i.h"

#ifndef CLFE_MATERIAL_H
#define CLFE_MATERIAL_H

#include "Texture.h"

namespace clfe
{

	template <typename T>
	Material* createSingleColorMaterial(T r, T g, T b, T a)
	{
		return new Material(createSingleColorTexture(r, g, b, a));
	}

	template <typename T>
	Material* createSingleColorMaterial(T r, T g, T b)
	{
		return new Material(createSingleColorTexture(r, g, b));
	}

	inline Material* RedMaterial()
	{
		return createSingleColorMaterial(1.0f, 0.0f, 0.0f, 1.0f);
	}

}

#endif