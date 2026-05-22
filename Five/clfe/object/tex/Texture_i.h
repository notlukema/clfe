#ifndef CLFE_TEXTURE_I_H
#define CLFE_TEXTURE_I_H

#include "clfe/Allocation.h"

#include "clm/VectorImpl.h"

#include "TypeTraits.h"
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

	template <uint8_t Channels, typename T>
	constexpr TextureType determineTextureType()
	{
		if constexpr (Channels == 3)
		{
			if constexpr (IsSame<T, int8_t>)
			{
				return TextureType::RGB8;
			}
			if constexpr (IsSame<T, uint8_t>)
			{
				return TextureType::RGBU8;
			}
			if constexpr (IsSame<T, float>)
			{
				if constexpr (sizeof(float) == 4)
				{
					return TextureType::RGB32F;
				}
				if constexpr (sizeof(float) == 2)
				{
					return TextureType::RGB16F;
				}
				return TextureType::INVALID;
			}
		}

		if constexpr (Channels == 4)
		{
			if constexpr (IsSame<T, int8_t>)
			{
				return TextureType::RGBA8;
			}
			if constexpr (IsSame<T, uint8_t>)
			{
				return TextureType::RGBAU8;
			}
			if constexpr (IsSame<T, float>)
			{
				if constexpr (sizeof(float) == 4)
				{
					return TextureType::RGBA32F;
				}
				if constexpr (sizeof(float) == 2)
				{
					return TextureType::RGBA16F;
				}
				return TextureType::INVALID;
			}
		}

		return TextureType::INVALID;
	}

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
		const TextureType type_;

		inline uint64_t index(uint32_t x, uint32_t y)
		{
			return (x + static_cast<uint64_t>(width_) * y) * Channels;
		}

	public:
		// Initializes with default allocation if data is nullptr
		Texture(uint32_t width, uint32_t height, T* data = nullptr, TextureType type = TextureType::INVALID) : width_(width), height_(height), size(width * height * Channels), data(data),
			type_(type == TextureType::INVALID ? determineTextureType<Channels, T>() : type)
		{
			if (data == nullptr)
			{
				this->data = (T*)malloc(size * sizeof(T));
			}
		}

		~Texture()
		{
			// figure out later
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
			return Channels;
		}

		Vector<Channels, T> get(uint32_t x, uint32_t y)
		{
			uint64_t i = index(x, y);
			T arr[Channels];
			for (uint8_t j = 0; j < Channels; j++)
			{
				arr[j] = data[i + j];
			}
			return Vector<Channels, T>(arr);
		}

		void set(uint32_t x, uint32_t y, const Vector<Channels, T>& value)
		{
			uint64_t i = index(x, y);
			for (uint8_t j = 0; j < Channels; j++)
			{
				data[i + j] = value[j];
			}
		}

		template <typename... Args>
		void set(uint32_t x, uint32_t y, Args... args) requires CompatibleTexArgs<Channels, T, Args...>
		{
			uint64_t i = index(x, y);
			uint8_t j = 0;
			((data[i + j++] = args), ...);
		}

	};

}

#endif