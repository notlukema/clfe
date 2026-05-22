#ifndef CLFE_TEXTURE_RGB_I_H
#define CLFE_TEXTURE_RGB_I_H

#include "Texture_i.h"

namespace clfe
{

	template <typename T>
	class Texture<3, T>
	{
	private:
		const uint32_t width_, height_;
		const uint32_t size;
		T* data;
		const TextureType type_;

		inline uint64_t index(uint32_t x, uint32_t y)
		{
			return (x + static_cast<uint64_t>(width_) * y) * 3;
		}

	public:
		// Initializes with default allocation if data is nullptr
		Texture(uint32_t width, uint32_t height, T* data = nullptr, TextureType type = TextureType::INVALID) : width_(width), height_(height), size(width * height * 3), data(data),
			type_(type == TextureType::INVALID ? determineTextureType<3, T>() : type)
		{
			if (data == nullptr)
			{
				this->data = (T*)malloc(size * sizeof(T));
			}
		}

		inline TextureType type() const
		{
			return type_;
		}

		inline uint32_t width() const
		{
			return width_;
		}

		inline uint32_t height() const
		{
			return height_;
		}

		inline uint8_t channels() const
		{
			return 3;
		}

		Vector<3, T> get(uint32_t x, uint32_t y)
		{
			uint64_t i = index(x, y);
			return Vector<3, T>(data[i], data[i + 1], data[i + 2]);
		}

		void set(uint32_t x, uint32_t y, const Vector<3, T>& value)
		{
			uint64_t i = index(x, y);
			data[i] = value[0];
			data[i + 1] = value[1];
			data[i + 2] = value[2];
		}

		void set(uint32_t x, uint32_t y, T r, T g, T b)
		{
			uint64_t i = index(x, y);
			data[i] = r;
			data[i + 1] = g;
			data[i + 2] = b;
		}

	public: // TextureRGB specific

		inline T getR(uint32_t x, uint32_t y)
		{
			return data[index(x, y)];
		}

		inline T getG(uint32_t x, uint32_t y)
		{
			return data[index(x, y) + 1];
		}

		inline T getB(uint32_t x, uint32_t y)
		{
			return data[index(x, y) + 2];
		}

		inline Vector<3, T> getRGB(uint32_t x, uint32_t y)
		{
			return get(x, y);
		}

		inline void setR(uint32_t x, uint32_t y, T r)
		{
			data[index(x, y)] = r;
		}

		inline void setG(uint32_t x, uint32_t y, T g)
		{
			data[index(x, y) + 1] = g;
		}

		inline void setB(uint32_t x, uint32_t y, T b)
		{
			data[index(x, y) + 2] = b;
		}

		inline void setRGB(uint32_t x, uint32_t y, const Vector<3, T>& rgb)
		{
			set(x, y, rgb);
		}

		inline void setRGB(uint32_t x, uint32_t y, T r, T g, T b)
		{
			set(x, y, r, g, b);
		}

	};

}

#endif