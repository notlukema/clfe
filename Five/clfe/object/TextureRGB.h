#include "TextureImpl.h"

#ifndef CLFE_TEXTURE_RGB_H
#define CLFE_TEXTURE_RGB_H

#include <cstdint>

namespace clfe
{

	template <typename T>
	using TextureRGB = Texture<3, T>;

	using TextureRGB8 = Texture<3, int8_t>;
	using TextureRGBU8 = Texture<3, uint8_t>;

	using TextureRGBF = Texture<3, float>;

}

#endif