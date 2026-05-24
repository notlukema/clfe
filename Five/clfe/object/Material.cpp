#include "Material.h"

namespace clfe
{

	Material::Material(const uint32_t count, const TextureBase* textures) : count_(count), textures_(textures)
	{}

	Material::~Material()
	{
		// something, do later
	}

}