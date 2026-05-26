#include "EMesh_i.h"

namespace clfe
{

	EMesh::EMesh(EMaterial* material, uint32_t vertexCount, uint32_t indexCount, Vector<3, float>* vertices, Vector<2, float>** uvs, uint32_t* indices) :
		material_(material), vCount(vertexCount), iCount(indexCount), vertices_(vertices), uvs_{ nullptr }, indices_(indices)
	{
		for (uint8_t i = 0; i < UVChannelCount; i++)
		{
			this->uvs_[i] = uvs[i];
		}
		material_->addReference();
	}

	EMesh::~EMesh()
	{
		delete vertices_;
		for (uint8_t i = 0; i < UVChannelCount; i++)
		{
			delete uvs_[i];
		}
		delete indices_;
		material_->removeReference();
	}

}