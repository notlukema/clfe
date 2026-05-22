#ifndef CLFE_TEXTURE_RGBA8_H
#define CLFE_TEXTURE_RGBA8_H

#include "Texture_i.h"
#include "clfe/Allocation.h"
#include "clm/Vector.h"

#include <cstdint>

namespace clfe
{

	template <>
	class Texture<4, int8_t>
	{
	private:
		const uint32_t width_, height_;
		const uint32_t size;
		int8_t* data;

		inline uint64_t index(uint32_t x, uint32_t y)
		{
			return (x + static_cast<uint64_t>(width_) * y) * 4;
		}

	public:
		// Initializes with default allocation if data is nullptr
		Texture(uint32_t width, uint32_t height, int8_t* data = nullptr) : width_(width), height_(height), size(width * height * 4), data(data)
		{
			if (data == nullptr)
			{
				data = (int8_t*)malloc(size * sizeof(int8_t));
			}
		}

		inline TextureType type() const
		{
			return TextureType::RGBA8;
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
			return 4;
		}

		Vector<4, int8_t> get(uint32_t x, uint32_t y)
		{
			uint64_t i = index(x, y);
			return Vector<4, int8_t>(data[i], data[i + 1], data[i + 2], data[i + 3]);
		}

		void set(uint32_t x, uint32_t y, const Vector<4, int8_t>& rgba)
		{
			uint64_t i = index(x, y);
			data[i] = rgba.get(0);
			data[i + 1] = rgba.get(1);
			data[i + 2] = rgba.get(2);
			data[i + 3] = rgba.get(3);
		}

		void set(uint32_t x, uint32_t y, int8_t r, int8_t g, int8_t b, int8_t a)
		{
			uint64_t i = index(x, y);
			data[i] = r;
			data[i + 1] = g;
			data[i + 2] = b;
			data[i + 3] = a;
		}

		// TextureRGBA8 specific

		inline int8_t getR(uint32_t x, uint32_t y)
		{
			return data[index(x, y)];
		}

		inline int8_t getG(uint32_t x, uint32_t y)
		{
			return data[index(x, y) + 1];
		}

		inline int8_t getB(uint32_t x, uint32_t y)
		{
			return data[index(x, y) + 2];
		}

		inline int8_t getA(uint32_t x, uint32_t y)
		{
			return data[index(x, y) + 3];
		}

		inline Vector<4, int8_t> getRGBA(uint32_t x, uint32_t y)
		{
			return get(x, y);
		}

		Vector<3, int8_t> getRGB(uint32_t x, uint32_t y)
		{
			uint64_t i = index(x, y);
			return Vector<3, int8_t>(data[i], data[i + 1], data[i + 2]);
		}

		inline void setR(uint32_t x, uint32_t y, int8_t r)
		{
			data[index(x, y)] = r;
		}

		inline void setG(uint32_t x, uint32_t y, int8_t g)
		{
			data[index(x, y) + 1] = g;
		}

		inline void setB(uint32_t x, uint32_t y, int8_t b)
		{
			data[index(x, y) + 2] = b;
		}

		inline void setA(uint32_t x, uint32_t y, int8_t a)
		{
			data[index(x, y) + 3] = a;
		}

		inline void setRGBA(uint32_t x, uint32_t y, const Vector<4, int8_t>& rgba)
		{
			set(x, y, rgba);
		}

		inline void setRGBA(uint32_t x, uint32_t y, int8_t r, int8_t g, int8_t b, int8_t a)
		{
			set(x, y, r, g, b, a);
		}

		void setRGB(uint32_t x, uint32_t y, const Vector<3, int8_t>& rgb)
		{
			uint64_t i = index(x, y);
			data[i] = rgb.get(0);
			data[i + 1] = rgb.get(1);
			data[i + 2] = rgb.get(2);
		}

		void setRGB(uint32_t x, uint32_t y, int8_t r, int8_t g, int8_t b)
		{
			uint64_t i = index(x, y);
			data[i] = r;
			data[i + 1] = g;
			data[i + 2] = b;
		}

	};

}

#endif