#include "Material_i.h"

namespace clfe
{

	Material::Material(uint32_t count, TextureBase* textures) : count_(count), textures_(textures)
	{}

	Material::~Material()
	{
		// something, do later
	}

}