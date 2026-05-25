#include "TextureImpl.h"

#include "TextureRGB.h"
#include "TextureRGBA.h"

#include "clfe/Allocation.h"

#ifndef CLFE_TEXTURE_H
#define CLFE_TEXTURE_H

namespace clfe
{

	template <typename T>
	TextureRGB<T>* createSingleColorTexture(T r, T g, T b)
	{
		T* data = (T*)malloc(3 * sizeof(T));
		data[0] = r;
		data[1] = g;
		data[2] = b;
		return new TextureRGB<T>(1, 1, data);
	}
	
	template <typename T>
	TextureRGBA<T>* createSingleColorTexture(T r, T g, T b, T a)
	{
		T* data = (T*)malloc(4 * sizeof(T));
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;
		return new TextureRGBA<T>(1, 1, data);
	}

}

#endif