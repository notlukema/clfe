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

	// Texture base

	class TextureBase
	{
	protected:
		const TextureType type_;
		const uint8_t channels_;
		const uint32_t width_, height_, size_;

		uint32_t references_;
		bool deleteOnNoRef;

		TextureBase(TextureType type, uint8_t channels, uint32_t width, uint32_t height, bool deleteOnNoRef = true);

	public:
		virtual ~TextureBase() = default;

		virtual const void* getRawData() = 0;
		virtual TextureBase* copy(bool deleteOnNoRef) = 0;

		inline uint32_t references() const
		{
			return references_;
		}

		void addReference();
		void removeReference();

		inline bool deleteOnNoReferences() const
		{
			return deleteOnNoRef;
		}

		inline void setDeleteOnNoReferences(bool value)
		{
			deleteOnNoRef = value;
		}

		inline TextureType type() const
		{
			return type_;
		}

		inline uint8_t channels() const
		{
			return channels_;
		}

		inline uint32_t width() const
		{
			return width_;
		}

		inline uint32_t height() const
		{
			return height_;
		}

		inline uint32_t size() const
		{
			return size_;
		}

	};

	// Texture

	template <uint8_t Channels, typename T, typename... Args>
	concept CompatibleTexArgs = (sizeof...(Args) == Channels) && (ConvertibleTo<Args, T> && ...);

	template <uint8_t Channels, typename T>
	class Texture : public TextureBase
	{
	private:
		const T* data;

		inline uint64_t index(uint32_t x, uint32_t y)
		{
			return (x + static_cast<uint64_t>(width_) * y) * Channels;
		}

	public:
		// Initializes with default allocation if data is nullptr
		Texture(uint32_t width, uint32_t height, const T* data = nullptr, TextureType type = TextureType::INVALID, bool deleteOnNoRef = true) : TextureBase(type == TextureType::INVALID ? determineTextureType<Channels, T>() : type, Channels, width, height, deleteOnNoRef), data(data)
		{
			if (data == nullptr)
			{
				this->data = (T*)malloc(size_ * sizeof(T));
			}
		}

		virtual ~Texture() override
		{
			delete data;
		}

		inline const T* getData()
		{
			return data;
		}

		virtual const void* getRawData() override
		{
			return data;
		}

		virtual TextureBase* copy(bool deleteOnNoRef) override
		{
			T* newData = new T[size_];
			for (uint32_t i = 0; i < size_; i++)
			{
				newData[i] = data[i];
			}
			return new Texture<Channels, T>(width_, height_, newData, type_, deleteOnNoRef);
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