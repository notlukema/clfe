#ifndef CLFE_MATERIAL_I_H
#define CLFE_MATERIAL_I_H

#include "TextureImpl.h"

#include <cstdint>

namespace clfe
{

	class Material
	{
	private:
		const uint32_t count_;
		const TextureBase* textures_;

		// all sorts of stats

	public:
		Material(uint32_t count, TextureBase* textures);
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