#ifndef CLFE_OBJECT_ENGINE_H
#define CLFE_OBJECT_ENGINE_H

#include "Object_i.h"

#include "clfe/Allocation.h"

#include "clm/VectorImpl.h"

#include "TypeTraits.h"
#include "VectorList.h"

namespace clfe
{

	// Object types

	enum class ObjectType
	{

		Static = 1,
		Dynamic = 2

	};

	// Object

	class Scene;

	class EObject : public Object
	{
	private:
		const ObjectType type_;

		bool update;

		friend class Scene;
		EObject(uint32_t meshCount, Mesh** meshes, ObjectType type = ObjectType::Static, bool active = true, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());
		EObject(Mesh* mesh, ObjectType type = ObjectType::Static, bool active = true, Vector<3, float> pos = Vector<3, float>(), Quaternion rot = Quaternion());

		~EObject();

	public:
		inline ObjectType type() const
		{
			return type_;
		}

		inline bool needUpdate() const
		{
			return update;
		}

		inline void requestUpdate()
		{
			update = true;
		}

		// scripting here but not for now

	};

}

#endif