#include "Texture_i.h"

namespace clfe
{

	TextureBase::TextureBase(TextureType type, uint8_t channels, uint32_t width, uint32_t height, bool deleteOnNoRef) : type_(type), channels_(channels), width_(width), height_(height), size_(width* height* channels), deleteOnNoRef(deleteOnNoRef), references_(0)
	{}

	void TextureBase::addReference()
	{
		references_++;
	}

	void TextureBase::removeReference()
	{
		references_--;
		if (references_ <= 0 && deleteOnNoRef)
		{
			delete this;
		}
	}

}