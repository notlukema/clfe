#include "EObject_i.h"

namespace clfe
{

	EObject::EObject(uint32_t meshCount, EMesh** meshes, ObjectType type, bool active, Vector<3, float> pos, Quaternion rot) : meshCount(0), meshes(nullptr), update_(true)
	{
		update(meshCount, meshes, type, active, pos, rot);
	}

	EObject::~EObject()
	{
		clearData();
	}

	void EObject::clearData()
	{
		for (uint32_t i = 0; i < meshCount; i++)
		{
			delete meshes[i];
		}
		delete meshes;
	}

	void EObject::update(uint32_t meshCount, EMesh** meshes, ObjectType type, bool active, Vector<3, float> pos, Quaternion rot)
	{
		clearData();

		this->meshCount = meshCount;
		this->meshes = meshes;
		type_ = type;
		this->active = active;
		this->pos = pos;
		this->rot = rot;

		update_ = true;
	}

}