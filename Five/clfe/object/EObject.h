#ifndef CLFE_OBJECT_ENGINE_H
#define CLFE_OBJECT_ENGINE_H

#include "Object_i.h"

#include "clm/Vector2.h"
#include "clm/Vector3.h"

namespace clfe
{

	class EObject : public Object
	{
	private:
		Vector3f pos;
		// rotation? consider types

	public:
		EObject(ObjectType type = ObjectType::Static, bool active = true);
		EObject(Vector3f pos, ObjectType type = ObjectType::Static, bool active = true);
		//EObject(Vector3f pos/*, rot*/, ObjectType type = ObjectType::Static, bool active = true);

	public:
		// operator overloads for new and delete or smth
		// discourage using new and delete for objects since it allocates on random memory

	};

}

#endif