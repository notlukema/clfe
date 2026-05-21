#ifndef CLFE_TEXTURE_H
#define CLFE_TEXTURE_H

#include <stdlib.h>
#include <cstdint>

namespace clfe
{

	template <typename T>
	class Texture
	{
	private:
		const uint32_t width, height;
		const uint32_t size;
		T* data;

	public:
		// Initializes with default allocation if data is nullptr
		Texture(uint32_t width, uint32_t height, T* data = nullptr) : width(width), height(height), size(width * height), data(data)
		{
			if (data == nullptr)
			{
				data = (T*)malloc(size * sizeof(T));
			}
		}

	};

}

#endif