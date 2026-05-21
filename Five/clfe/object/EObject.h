#ifndef CLFE_OBJECT_ENGINE_H
#define CLFE_OBJECT_ENGINE_H

#include "Object_i.h"

#include "clm/Vector2.h"
#include "clm/Vector3.h"

namespace clfe
{

	// Object types

	enum class ObjectType
	{

		Dynamic = 1,
		Static = 2

	};

	class EObject : public Object
	{
	private:
		const ObjectType type;
		Vector3f pos;
		// rotation? consider types

		// Vertex data with up to 8 uv channels

	public:
		EObject(ObjectType type = ObjectType::Static, bool active = true);
		EObject(Vector3f pos, ObjectType type = ObjectType::Static, bool active = true);
		//EObject(Vector3f pos/*, rot*/, ObjectType type = ObjectType::Static, bool active = true);

		inline ObjectType getType() const
		{
			return type;
		}

	public:
		// operator overloads for new and delete or smth
		// discourage using new and delete for objects since it allocates on random memory

	};

}

#endif