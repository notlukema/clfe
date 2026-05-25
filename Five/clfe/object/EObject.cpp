#include "EObject.h"

namespace clfe
{

	EObject::EObject(uint32_t meshCount, Mesh** meshes, ObjectType type, bool active, Vector<3, float> pos, Quaternion rot) : Object(meshCount, meshes, active, pos, rot), type_(type), update(true)
	{}

	EObject::EObject(Mesh* mesh, ObjectType type, bool active, Vector<3, float> pos, Quaternion rot) : Object(mesh, active, pos, rot), type_(type), update(true)
	{}

	EObject::~EObject()
	{
	}

}