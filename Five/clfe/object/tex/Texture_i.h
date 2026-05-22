#ifndef CLFE_TEXTURE_I_H
#define CLFE_TEXTURE_I_H

#include "clfe/Allocation.h"

#include "clm/Vector.h"

#include "Concepts.h"

#include <cstdint>

namespace clfe
{

	// Texture types (these help renderers to know what type of texture to map to)

	enum class TextureType
	{

		INVALID = 0,
		RGB8 = 1,
		RGBA8 = 2,
		RGBU8 = 3,
		RGBAU8 = 4,
		RGB16F = 5,
		RGBA16F = 6,
		RGB32F = 7,
		RGBA32F = 8

	};

	// Texture

	template <uint8_t Channels, typename T, typename... Args>
	concept CompatibleTexArgs = (sizeof...(Args) == Channels) && (ConvertibleTo<Args, T> && ...);

	template <uint8_t Channels, typename T>
	class Texture
	{
	private:
		const uint32_t width_, height_;
		const uint32_t size;
		T* data;

		inline uint64_t index(uint32_t x, uint32_t y)
		{
			return (x + static_cast<uint64_t>(width_) * y) * Channels;
		}

	public:
		// Initializes with default allocation if data is nullptr
		Texture(uint32_t width, uint32_t height, T* data = nullptr) : width_(width), height_(height), size(width * height * Channels), data(data)
		{
			if (data == nullptr)
			{
				data = (T*)malloc(size * sizeof(T));
			}
		}

		inline TextureType type() const
		{
			return TextureType::INVALID;
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
			return Channels;
		}

		Vector<Channels, T> get(uint32_t x, uint32_t y)
		{
			uint64_t i = index(x, y);
			return Vector<Channels, T>(data[i], data[i + 1], data[i + 2], data[i + 3]);
		}

		void set(uint32_t x, uint32_t y, const Vector<Channels, T>& value)
		{
			// Partially unrolled
			uint64_t i = index(x, y);
			if constexpr (Channels >= 1)
			{
				data[i] = value[0];
			}
			if constexpr (Channels >= 2)
			{
				data[i + 1] = value[1];
			}
			if constexpr (Channels >= 3)
			{
				data[i + 2] = value[2];
			}
			if constexpr (Channels >= 4)
			{
				data[i + 3] = value[3];
			}
			if constexpr (Channels >= 5)
			{
				for (uint8_t c = 4; c < Channels; c++)
				{
					data[i + c] = value[c];
				}
			}
		}

		template <typename... Args>
		void set(uint32_t x, uint32_t y, Args... args) requires CompatibleTexArgs<Channels, T, Args...>
		{
			// Fully unrolled
			uint64_t i = index(x, y);
			uint8_t j = 0;
			((data[i + j++] = args), ...);
		}

	};

}

#endif