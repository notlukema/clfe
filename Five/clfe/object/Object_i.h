#ifndef CLFE_OBJECT_I_H
#define CLFE_OBJECT_I_H

#include "Mesh.h"

#include "clm/VectorImpl.h"
#include "clm/Quaternion.h"

#include <cstdint>

namespace clfe
{


	// Object

	class Object
	{
	protected:
		bool active;

		Vector<3, float> pos;
		Quaternion rot;

		uint32_t meshCount;
		Mesh** meshes;

		Object(uint32_t meshCount, Mesh** meshes, bool active = true, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());
		Object(Mesh* mesh, bool active = true, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());
		// constructor skipping creating a mesh here

	public:
		~Object();

		inline bool isActive() const
		{
			return active;
		}

		inline void deactivate()
		{
			active = false;
		}

		inline void activate()
		{
			active = true;
		}

		inline void setActive(bool active)
		{
			this->active = active;
		}

	};

}

#endif