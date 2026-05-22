#include "TextureImpl.h"

#ifndef CLFE_TEXTURE_RGBA_H
#define CLFE_TEXTURE_RGBA_H

#include <cstdint>

namespace clfe
{

	template <typename T>
	using TextureRGBA = Texture<4, T>;

	using TextureRGBA8 = Texture<4, int8_t>;
	using TextureRGBAU8 = Texture<4, uint8_t>;

	using TextureRGBAF = Texture<4, float>;

}

#endif