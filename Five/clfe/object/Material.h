#ifndef CLFE_MATERIAL_H
#define CLFE_MATERIAL_H

#include "TextureImpl.h"

#include <cstdint>

namespace clfe
{

	class Material
	{
	private:
		const uint32_t count_;
		const TextureBase* textures_;

	public:
		Material(const uint32_t count, const TextureBase* textures);
		~Material();

		inline uint32_t count()
		{
			return count_;
		}

		inline const TextureBase* textures()
		{
			return textures_;
		}

	};

}

#endif