#include "Object_i.h"

namespace clfe
{

	Object::Object(uint32_t vertexCount, uint32_t indexCount, Vector<3, float>* vertices, Vector<2, float>** uvs, uint32_t* indices, Vector<3, float> pos, Quaternion rot, bool active) : 
		vCount(vertexCount), iCount(indexCount), vertices(vertices), uvs{ nullptr }, indices(indices), pos(pos), rot(rot), active(active)
	{
		for (uint8_t i = 0; i < UVChannelCount; i++)
		{
			this->uvs[i] = uvs[i];
		}
	}

	Object::~Object()
	{
		delete vertices;
		for (uint8_t i = 0; i < UVChannelCount; i++)
		{
			delete uvs[i];
		}
		delete indices;
	}

}