#include "Object_i.h"

#include "clfe/Allocation.h"

namespace clfe
{

	Object::Object(uint32_t meshCount, Mesh** meshes, bool active, Vector<3, float> pos, Quaternion rot) : meshCount(meshCount), meshes(meshes), active(active), pos(pos), rot(rot)
	{}

	Object::Object(Mesh* mesh, bool active, Vector<3, float> pos, Quaternion rot) : meshCount(1), active(active), pos(pos), rot(rot)
	{
		meshes = (Mesh**)malloc(sizeof(Mesh*));
		meshes[0] = mesh;
	}

	Object::~Object()
	{
		for (uint32_t i = 0; i < meshCount; i++)
		{
			delete meshes[i];
		}
		delete meshes;
	}

}