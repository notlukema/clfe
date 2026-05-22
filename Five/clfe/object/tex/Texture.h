#include "Texture_i.h"

#include "TextureRGBA8.h"
#include "TextureRGBAF.h"

#ifndef CLFE_TEXTURE_H
#define CLFE_TEXTURE_H

#include <cstdint>

using namespace std;

namespace clfe
{

	template <typename T>
	using TextureRGB = Texture<3, T>;

	template <typename T>
	using TextureRGBA = Texture<4, T>;

	using TextureRGB8 = Texture<3, int8_t>;
	using TextureRGBA8 = Texture<4, int8_t>;
	using TextureRGBU8 = Texture<3, uint8_t>;
	using TextureRGBAU8 = Texture<4, uint8_t>;

	// Visual Studio doesn't support stdfloat yet so we're improvising with "compile time dynamic type finding" to detect for floats of size 16 or 32 bits
	using TextureRGBF = Texture<3, float>;
	using TextureRGBAF = Texture<4, float>;

}

#endif